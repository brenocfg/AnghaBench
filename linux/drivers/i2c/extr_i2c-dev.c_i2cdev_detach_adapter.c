#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i2c_dev {int /*<<< orphan*/  cdev; } ;
struct i2c_adapter {int /*<<< orphan*/  name; int /*<<< orphan*/  nr; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 int /*<<< orphan*/  i2c_dev_class ; 
 struct i2c_dev* i2c_dev_get_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_i2c_dev (struct i2c_dev*) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 

__attribute__((used)) static int i2cdev_detach_adapter(struct device *dev, void *dummy)
{
	struct i2c_adapter *adap;
	struct i2c_dev *i2c_dev;

	if (dev->type != &i2c_adapter_type)
		return 0;
	adap = to_i2c_adapter(dev);

	i2c_dev = i2c_dev_get_by_minor(adap->nr);
	if (!i2c_dev) /* attach_adapter must have failed */
		return 0;

	cdev_del(&i2c_dev->cdev);
	put_i2c_dev(i2c_dev);
	device_destroy(i2c_dev_class, MKDEV(I2C_MAJOR, adap->nr));

	pr_debug("i2c-dev: adapter [%s] unregistered\n", adap->name);
	return 0;
}