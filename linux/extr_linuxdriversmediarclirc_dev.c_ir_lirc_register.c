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
struct TYPE_4__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/  class; } ;
struct rc_dev {int driver_type; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  dev; scalar_t__ tx_ir; TYPE_1__ lirc_dev; int /*<<< orphan*/  lirc_cdev; int /*<<< orphan*/  lirc_fh_lock; int /*<<< orphan*/  lirc_fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RC_DEV_MAX ; 
#define  RC_DRIVER_IR_RAW 129 
#define  RC_DRIVER_SCANCODE 128 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char const*,char const*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lirc_base_dev ; 
 int /*<<< orphan*/  lirc_class ; 
 int /*<<< orphan*/  lirc_fops ; 
 int /*<<< orphan*/  lirc_ida ; 
 int /*<<< orphan*/  lirc_release_device ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ir_lirc_register(struct rc_dev *dev)
{
	const char *rx_type, *tx_type;
	int err, minor;

	minor = ida_simple_get(&lirc_ida, 0, RC_DEV_MAX, GFP_KERNEL);
	if (minor < 0)
		return minor;

	device_initialize(&dev->lirc_dev);
	dev->lirc_dev.class = lirc_class;
	dev->lirc_dev.parent = &dev->dev;
	dev->lirc_dev.release = lirc_release_device;
	dev->lirc_dev.devt = MKDEV(MAJOR(lirc_base_dev), minor);
	dev_set_name(&dev->lirc_dev, "lirc%d", minor);

	INIT_LIST_HEAD(&dev->lirc_fh);
	spin_lock_init(&dev->lirc_fh_lock);

	cdev_init(&dev->lirc_cdev, &lirc_fops);

	err = cdev_device_add(&dev->lirc_cdev, &dev->lirc_dev);
	if (err)
		goto out_ida;

	get_device(&dev->dev);

	switch (dev->driver_type) {
	case RC_DRIVER_SCANCODE:
		rx_type = "scancode";
		break;
	case RC_DRIVER_IR_RAW:
		rx_type = "raw IR";
		break;
	default:
		rx_type = "no";
		break;
	}

	if (dev->tx_ir)
		tx_type = "raw IR";
	else
		tx_type = "no";

	dev_info(&dev->dev, "lirc_dev: driver %s registered at minor = %d, %s receiver, %s transmitter",
		 dev->driver_name, minor, rx_type, tx_type);

	return 0;

out_ida:
	ida_simple_remove(&lirc_ida, minor);
	return err;
}