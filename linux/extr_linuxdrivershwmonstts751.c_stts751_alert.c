#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stts751_priv {int max_alert; int min_alert; int notify_max; int notify_min; int /*<<< orphan*/  access_lock; TYPE_1__* dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum i2c_alert_protocol { ____Placeholder_i2c_alert_protocol } i2c_alert_protocol ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int I2C_PROTOCOL_SMBUS_ALERT ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct stts751_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stts751_update_alert (struct stts751_priv*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void stts751_alert(struct i2c_client *client,
			  enum i2c_alert_protocol type, unsigned int data)
{
	int ret;
	struct stts751_priv *priv = i2c_get_clientdata(client);

	if (type != I2C_PROTOCOL_SMBUS_ALERT)
		return;

	dev_dbg(&client->dev, "alert!");

	mutex_lock(&priv->access_lock);
	ret = stts751_update_alert(priv);
	if (ret < 0) {
		/* default to worst case */
		priv->max_alert = true;
		priv->min_alert = true;

		dev_warn(priv->dev,
			 "Alert received, but can't communicate to the device. Triggering all alarms!");
	}

	if (priv->max_alert) {
		if (priv->notify_max)
			dev_notice(priv->dev, "got alert for HIGH temperature");
		priv->notify_max = false;

		/* unblock alert poll */
		sysfs_notify(&priv->dev->kobj, NULL, "temp1_max_alarm");
	}

	if (priv->min_alert) {
		if (priv->notify_min)
			dev_notice(priv->dev, "got alert for LOW temperature");
		priv->notify_min = false;

		/* unblock alert poll */
		sysfs_notify(&priv->dev->kobj, NULL, "temp1_min_alarm");
	}

	if (priv->min_alert || priv->max_alert)
		kobject_uevent(&priv->dev->kobj, KOBJ_CHANGE);

	mutex_unlock(&priv->access_lock);
}