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
struct edp_ctrl {int /*<<< orphan*/  off_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  on_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void msm_edp_ctrl_power(struct edp_ctrl *ctrl, bool on)
{
	if (on)
		queue_work(ctrl->workqueue, &ctrl->on_work);
	else
		queue_work(ctrl->workqueue, &ctrl->off_work);
}