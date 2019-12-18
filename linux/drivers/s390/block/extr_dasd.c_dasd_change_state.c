#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {scalar_t__ state; scalar_t__ target; TYPE_2__* cdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int dasd_decrease_state (struct dasd_device*) ; 
 int dasd_increase_state (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_init_waitq ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_change_state(struct dasd_device *device)
{
	int rc;

	if (device->state == device->target)
		/* Already where we want to go today... */
		return;
	if (device->state < device->target)
		rc = dasd_increase_state(device);
	else
		rc = dasd_decrease_state(device);
	if (rc == -EAGAIN)
		return;
	if (rc)
		device->target = device->state;

	/* let user-space know that the device status changed */
	kobject_uevent(&device->cdev->dev.kobj, KOBJ_CHANGE);

	if (device->state == device->target)
		wake_up(&dasd_init_waitq);
}