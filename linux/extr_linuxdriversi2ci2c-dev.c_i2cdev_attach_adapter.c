#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct i2c_dev {TYPE_1__ cdev; struct i2c_dev* dev; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MAJOR ; 
 scalar_t__ IS_ERR (struct i2c_dev*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct i2c_dev*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct i2c_dev* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct i2c_dev* get_free_i2c_dev (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 int /*<<< orphan*/  i2c_dev_class ; 
 int /*<<< orphan*/  i2cdev_fops ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_i2c_dev (struct i2c_dev*) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 

__attribute__((used)) static int i2cdev_attach_adapter(struct device *dev, void *dummy)
{
	struct i2c_adapter *adap;
	struct i2c_dev *i2c_dev;
	int res;

	if (dev->type != &i2c_adapter_type)
		return 0;
	adap = to_i2c_adapter(dev);

	i2c_dev = get_free_i2c_dev(adap);
	if (IS_ERR(i2c_dev))
		return PTR_ERR(i2c_dev);

	cdev_init(&i2c_dev->cdev, &i2cdev_fops);
	i2c_dev->cdev.owner = THIS_MODULE;
	res = cdev_add(&i2c_dev->cdev, MKDEV(I2C_MAJOR, adap->nr), 1);
	if (res)
		goto error_cdev;

	/* register this i2c device with the driver core */
	i2c_dev->dev = device_create(i2c_dev_class, &adap->dev,
				     MKDEV(I2C_MAJOR, adap->nr), NULL,
				     "i2c-%d", adap->nr);
	if (IS_ERR(i2c_dev->dev)) {
		res = PTR_ERR(i2c_dev->dev);
		goto error;
	}

	pr_debug("i2c-dev: adapter [%s] registered as minor %d\n",
		 adap->name, adap->nr);
	return 0;
error:
	cdev_del(&i2c_dev->cdev);
error_cdev:
	put_i2c_dev(i2c_dev);
	return res;
}