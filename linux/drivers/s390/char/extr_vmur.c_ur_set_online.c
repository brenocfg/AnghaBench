#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int devno; } ;
struct urdev {scalar_t__ class; TYPE_5__* char_device; int /*<<< orphan*/  device; TYPE_3__* cdev; TYPE_1__ dev_id; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; TYPE_4__* ops; } ;
struct TYPE_11__ {int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {scalar_t__ cu_type; } ;
struct TYPE_10__ {TYPE_2__ id; } ;

/* Variables and functions */
 scalar_t__ DEV_CLASS_UR_I ; 
 scalar_t__ DEV_CLASS_UR_O ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int,int) ; 
 scalar_t__ PRINTER_DEVTYPE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ READER_PUNCH_DEVTYPE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int cdev_add (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* cdev_alloc () ; 
 int /*<<< orphan*/  cdev_del (TYPE_5__*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  ur_first_dev_maj_min ; 
 TYPE_4__ ur_fops ; 
 struct urdev* urdev_get_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  urdev_put (struct urdev*) ; 
 int /*<<< orphan*/  vmur_class ; 
 int /*<<< orphan*/  vmur_mutex ; 

__attribute__((used)) static int ur_set_online(struct ccw_device *cdev)
{
	struct urdev *urd;
	int minor, major, rc;
	char node_id[16];

	TRACE("ur_set_online: cdev=%p\n", cdev);

	mutex_lock(&vmur_mutex);
	urd = urdev_get_from_cdev(cdev);
	if (!urd) {
		/* ur_remove already deleted our urd */
		rc = -ENODEV;
		goto fail_unlock;
	}

	if (urd->char_device) {
		/* Another ur_set_online was faster */
		rc = -EBUSY;
		goto fail_urdev_put;
	}

	minor = urd->dev_id.devno;
	major = MAJOR(ur_first_dev_maj_min);

	urd->char_device = cdev_alloc();
	if (!urd->char_device) {
		rc = -ENOMEM;
		goto fail_urdev_put;
	}

	urd->char_device->ops = &ur_fops;
	urd->char_device->owner = ur_fops.owner;

	rc = cdev_add(urd->char_device, MKDEV(major, minor), 1);
	if (rc)
		goto fail_free_cdev;
	if (urd->cdev->id.cu_type == READER_PUNCH_DEVTYPE) {
		if (urd->class == DEV_CLASS_UR_I)
			sprintf(node_id, "vmrdr-%s", dev_name(&cdev->dev));
		if (urd->class == DEV_CLASS_UR_O)
			sprintf(node_id, "vmpun-%s", dev_name(&cdev->dev));
	} else if (urd->cdev->id.cu_type == PRINTER_DEVTYPE) {
		sprintf(node_id, "vmprt-%s", dev_name(&cdev->dev));
	} else {
		rc = -EOPNOTSUPP;
		goto fail_free_cdev;
	}

	urd->device = device_create(vmur_class, &cdev->dev,
				    urd->char_device->dev, NULL, "%s", node_id);
	if (IS_ERR(urd->device)) {
		rc = PTR_ERR(urd->device);
		TRACE("ur_set_online: device_create rc=%d\n", rc);
		goto fail_free_cdev;
	}
	urdev_put(urd);
	mutex_unlock(&vmur_mutex);
	return 0;

fail_free_cdev:
	cdev_del(urd->char_device);
	urd->char_device = NULL;
fail_urdev_put:
	urdev_put(urd);
fail_unlock:
	mutex_unlock(&vmur_mutex);
	return rc;
}