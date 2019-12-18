#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pam; scalar_t__ dev; } ;
struct TYPE_7__ {TYPE_1__ pmcw; } ;
struct subchannel {int lpm; int opm; int /*<<< orphan*/  schid; TYPE_2__ schib; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_4__* private; TYPE_5__ dev; } ;
struct TYPE_8__ {scalar_t__ devno; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_3__ dev_id; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  ccw_device_start_id (struct ccw_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ cio_commit_config (struct subchannel*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  css_schedule_eval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_subchannel_init_config (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

void ccw_device_trigger_reprobe(struct ccw_device *cdev)
{
	struct subchannel *sch;

	if (cdev->private->state != DEV_STATE_DISCONNECTED)
		return;

	sch = to_subchannel(cdev->dev.parent);
	/* Update some values. */
	if (cio_update_schib(sch))
		return;
	/*
	 * The pim, pam, pom values may not be accurate, but they are the best
	 * we have before performing device selection :/
	 */
	sch->lpm = sch->schib.pmcw.pam & sch->opm;
	/*
	 * Use the initial configuration since we can't be shure that the old
	 * paths are valid.
	 */
	io_subchannel_init_config(sch);
	if (cio_commit_config(sch))
		return;

	/* We should also udate ssd info, but this has to wait. */
	/* Check if this is another device which appeared on the same sch. */
	if (sch->schib.pmcw.dev != cdev->private->dev_id.devno)
		css_schedule_eval(sch->schid);
	else
		ccw_device_start_id(cdev, 0);
}