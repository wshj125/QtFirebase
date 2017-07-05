#ifndef QTFIREBASESERVICE_H
#define QTFIREBASESERVICE_H
#include <QObject>
#include "qtfirebase.h"
#include "firebase/variant.h"

template <typename ResultType> const ResultType* result(const void* p) {
  return p==nullptr ? nullptr : static_cast<const ResultType*>(p);
}

class QtFirebaseService: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ready READ ready NOTIFY readyChanged)
public:
    QtFirebaseService(QObject* parent);
    bool ready() const;
    static QVariant fromFirebaseVariant(const firebase::Variant& v);
    static firebase::Variant fromQtVariant(const QVariant& v);
signals:
    void readyChanged();

protected:

    void startInit();
    virtual void setReady(bool value);
    virtual bool initializing() const;
    virtual void setInitializing(bool value);
    virtual void init() = 0;
    virtual void onFutureEvent(QString eventId, firebase::FutureBase future) = 0;

    QString __QTFIREBASE_ID;
    bool _ready;
    bool _initializing;
};

#endif // QTFIREBASESERVICE_H
