#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urdev {TYPE_1__* char_device; int /*<<< orphan*/  ref_count; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 struct urdev* urdev_get_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  urdev_put (struct urdev*) ; 
 int /*<<< orphan*/  vmur_class ; 

__attribute__((used)) static int ur_set_offline_force(struct ccw_device *cdev, int force)
{
	struct urdev *urd;
	int rc;

	TRACE("ur_set_offline: cdev=%p\n", cdev);
	urd = urdev_get_from_cdev(cdev);
	if (!urd)
		/* ur_remove already deleted our urd */
		return -ENODEV;
	if (!urd->char_device) {
		/* Another ur_set_offline was faster */
		rc = -EBUSY;
		goto fail_urdev_put;
	}
	if (!force && (refcount_read(&urd->ref_count) > 2)) {
		/* There is still a user of urd (e.g. ur_open) */
		TRACE("ur_set_offline: BUSY\n");
		rc = -EBUSY;
		goto fail_urdev_put;
	}
	device_destroy(vmur_class, urd->char_device->dev);
	cdev_del(urd->char_device);
	urd->char_device = NULL;
	rc = 0;

fail_urdev_put:
	urdev_put(urd);
	return rc;
}