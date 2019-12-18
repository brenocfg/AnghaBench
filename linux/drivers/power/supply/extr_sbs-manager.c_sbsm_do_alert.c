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
struct i2c_driver {int /*<<< orphan*/  (* alert ) (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ driver; } ;
struct i2c_client {int addr; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  I2C_PROTOCOL_SMBUS_ALERT ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 struct i2c_client* i2c_verify_client (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_driver* to_i2c_driver (scalar_t__) ; 

__attribute__((used)) static int sbsm_do_alert(struct device *dev, void *d)
{
	struct i2c_client *client = i2c_verify_client(dev);
	struct i2c_driver *driver;

	if (!client || client->addr != 0x0b)
		return 0;

	device_lock(dev);
	if (client->dev.driver) {
		driver = to_i2c_driver(client->dev.driver);
		if (driver->alert)
			driver->alert(client, I2C_PROTOCOL_SMBUS_ALERT, 0);
		else
			dev_warn(&client->dev, "no driver alert()!\n");
	} else {
		dev_dbg(&client->dev, "alert with no driver\n");
	}
	device_unlock(dev);

	return -EBUSY;
}