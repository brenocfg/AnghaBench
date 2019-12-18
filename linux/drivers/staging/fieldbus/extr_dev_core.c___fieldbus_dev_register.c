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
struct fieldbus_dev {int id; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; int /*<<< orphan*/  dc_wq; int /*<<< orphan*/  fieldbus_id_get; int /*<<< orphan*/  write_area; int /*<<< orphan*/  read_area; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_FIELDBUSES ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fieldbus_dev*,char*,int) ; 
 int /*<<< orphan*/  fieldbus_class ; 
 int /*<<< orphan*/  fieldbus_devt ; 
 int /*<<< orphan*/  fieldbus_fops ; 
 int /*<<< orphan*/  fieldbus_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __fieldbus_dev_register(struct fieldbus_dev *fb)
{
	dev_t devno;
	int err;

	if (!fb)
		return -EINVAL;
	if (!fb->read_area || !fb->write_area || !fb->fieldbus_id_get)
		return -EINVAL;
	fb->id = ida_simple_get(&fieldbus_ida, 0, MAX_FIELDBUSES, GFP_KERNEL);
	if (fb->id < 0)
		return fb->id;
	devno = MKDEV(MAJOR(fieldbus_devt), fb->id);
	init_waitqueue_head(&fb->dc_wq);
	cdev_init(&fb->cdev, &fieldbus_fops);
	err = cdev_add(&fb->cdev, devno, 1);
	if (err) {
		pr_err("fieldbus_dev%d unable to add device %d:%d\n",
		       fb->id, MAJOR(fieldbus_devt), fb->id);
		goto err_cdev;
	}
	fb->dev = device_create(&fieldbus_class, fb->parent, devno, fb,
				"fieldbus_dev%d", fb->id);
	if (IS_ERR(fb->dev)) {
		err = PTR_ERR(fb->dev);
		goto err_dev_create;
	}
	return 0;

err_dev_create:
	cdev_del(&fb->cdev);
err_cdev:
	ida_simple_remove(&fieldbus_ida, fb->id);
	return err;
}