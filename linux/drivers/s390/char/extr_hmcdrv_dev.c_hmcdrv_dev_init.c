#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  devnode; } ;
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {TYPE_1__ dev; scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMCDRV_DEV_CLASS ; 
 int /*<<< orphan*/  HMCDRV_DEV_NAME ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct device* class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (struct device*) ; 
 struct device* device_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ hmcdrv_dev ; 
 struct device* hmcdrv_dev_class ; 
 int /*<<< orphan*/  hmcdrv_dev_fops ; 
 int /*<<< orphan*/  hmcdrv_dev_name ; 
 int /*<<< orphan*/  hmcdrv_dev_no ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

int hmcdrv_dev_init(void)
{
	int rc;

#ifdef HMCDRV_DEV_CLASS
	struct device *dev;

	rc = alloc_chrdev_region(&hmcdrv_dev_no, 0, 1, HMCDRV_DEV_NAME);

	if (rc)
		goto out_err;

	cdev_init(&hmcdrv_dev.dev, &hmcdrv_dev_fops);
	hmcdrv_dev.dev.owner = THIS_MODULE;
	rc = cdev_add(&hmcdrv_dev.dev, hmcdrv_dev_no, 1);

	if (rc)
		goto out_unreg;

	/* At this point the character device exists in the kernel (see
	 * /proc/devices), but not under /dev nor /sys/devices/virtual. So
	 * we have to create an associated class (see /sys/class).
	 */
	hmcdrv_dev_class = class_create(THIS_MODULE, HMCDRV_DEV_CLASS);

	if (IS_ERR(hmcdrv_dev_class)) {
		rc = PTR_ERR(hmcdrv_dev_class);
		goto out_devdel;
	}

	/* Finally a device node in /dev has to be established (as 'mkdev'
	 * does from the command line). Notice that assignment of a device
	 * node name/mode function is optional (only for mode != 0600).
	 */
	hmcdrv_dev.mode = 0; /* "unset" */
	hmcdrv_dev_class->devnode = hmcdrv_dev_name;

	dev = device_create(hmcdrv_dev_class, NULL, hmcdrv_dev_no, NULL,
			    "%s", HMCDRV_DEV_NAME);
	if (!IS_ERR(dev))
		return 0;

	rc = PTR_ERR(dev);
	class_destroy(hmcdrv_dev_class);
	hmcdrv_dev_class = NULL;

out_devdel:
	cdev_del(&hmcdrv_dev.dev);

out_unreg:
	unregister_chrdev_region(hmcdrv_dev_no, 1);

out_err:

#else  /* !HMCDRV_DEV_CLASS */
	hmcdrv_dev.dev.minor = MISC_DYNAMIC_MINOR;
	hmcdrv_dev.dev.name = HMCDRV_DEV_NAME;
	hmcdrv_dev.dev.fops = &hmcdrv_dev_fops;
	hmcdrv_dev.dev.mode = 0; /* finally produces 0600 */
	rc = misc_register(&hmcdrv_dev.dev);
#endif	/* HMCDRV_DEV_CLASS */

	return rc;
}