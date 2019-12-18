#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__ pam; } ;
struct TYPE_7__ {TYPE_2__ pmcw; } ;
struct subchannel {scalar_t__ opm; scalar_t__ vpm; TYPE_3__ schib; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_4__* private; TYPE_1__ dev; } ;
struct TYPE_8__ {scalar_t__ path_broken_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_schedule_recovery () ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_device_handle_broken_paths(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	u8 broken_paths = (sch->schib.pmcw.pam & sch->opm) ^ sch->vpm;

	if (broken_paths && (cdev->private->path_broken_mask != broken_paths))
		ccw_device_schedule_recovery();

	cdev->private->path_broken_mask = broken_paths;
}