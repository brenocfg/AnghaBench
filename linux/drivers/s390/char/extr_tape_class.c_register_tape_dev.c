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
struct tape_class_device {char* device_name; char* mode_name; TYPE_2__* char_device; TYPE_1__* class_device; } ;
struct file_operations {int /*<<< orphan*/  owner; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_7__ {int /*<<< orphan*/  dev; struct file_operations const* ops; int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tape_class_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  TAPECLASS_NAME_LEN ; 
 int cdev_add (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cdev_alloc () ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 TYPE_1__* device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tape_class_device*) ; 
 struct tape_class_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tape_class ; 

struct tape_class_device *register_tape_dev(
	struct device *		device,
	dev_t			dev,
	const struct file_operations *fops,
	char *			device_name,
	char *			mode_name)
{
	struct tape_class_device *	tcd;
	int		rc;
	char *		s;

	tcd = kzalloc(sizeof(struct tape_class_device), GFP_KERNEL);
	if (!tcd)
		return ERR_PTR(-ENOMEM);

	strlcpy(tcd->device_name, device_name, TAPECLASS_NAME_LEN);
	for (s = strchr(tcd->device_name, '/'); s; s = strchr(s, '/'))
		*s = '!';
	strlcpy(tcd->mode_name, mode_name, TAPECLASS_NAME_LEN);
	for (s = strchr(tcd->mode_name, '/'); s; s = strchr(s, '/'))
		*s = '!';

	tcd->char_device = cdev_alloc();
	if (!tcd->char_device) {
		rc = -ENOMEM;
		goto fail_with_tcd;
	}

	tcd->char_device->owner = fops->owner;
	tcd->char_device->ops   = fops;

	rc = cdev_add(tcd->char_device, dev, 1);
	if (rc)
		goto fail_with_cdev;

	tcd->class_device = device_create(tape_class, device,
					  tcd->char_device->dev, NULL,
					  "%s", tcd->device_name);
	rc = PTR_ERR_OR_ZERO(tcd->class_device);
	if (rc)
		goto fail_with_cdev;
	rc = sysfs_create_link(
		&device->kobj,
		&tcd->class_device->kobj,
		tcd->mode_name
	);
	if (rc)
		goto fail_with_class_device;

	return tcd;

fail_with_class_device:
	device_destroy(tape_class, tcd->char_device->dev);

fail_with_cdev:
	cdev_del(tcd->char_device);

fail_with_tcd:
	kfree(tcd);

	return ERR_PTR(rc);
}