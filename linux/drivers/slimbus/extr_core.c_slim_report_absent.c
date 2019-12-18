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
struct slim_device {int is_laddr_valid; int /*<<< orphan*/  laddr; struct slim_controller* ctrl; } ;
struct slim_controller {int /*<<< orphan*/  laddr_ida; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIM_DEVICE_STATUS_DOWN ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_device_update_status (struct slim_device*,int /*<<< orphan*/ ) ; 

void slim_report_absent(struct slim_device *sbdev)
{
	struct slim_controller *ctrl = sbdev->ctrl;

	if (!ctrl)
		return;

	/* invalidate logical addresses */
	mutex_lock(&ctrl->lock);
	sbdev->is_laddr_valid = false;
	mutex_unlock(&ctrl->lock);

	ida_simple_remove(&ctrl->laddr_ida, sbdev->laddr);
	slim_device_update_status(sbdev, SLIM_DEVICE_STATUS_DOWN);
}