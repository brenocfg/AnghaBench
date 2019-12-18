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
struct edp_ctrl {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/ * edid; int /*<<< orphan*/ * aux; TYPE_1__* pdev; int /*<<< orphan*/ * workqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_edp_aux_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void msm_edp_ctrl_destroy(struct edp_ctrl *ctrl)
{
	if (!ctrl)
		return;

	if (ctrl->workqueue) {
		flush_workqueue(ctrl->workqueue);
		destroy_workqueue(ctrl->workqueue);
		ctrl->workqueue = NULL;
	}

	if (ctrl->aux) {
		msm_edp_aux_destroy(&ctrl->pdev->dev, ctrl->aux);
		ctrl->aux = NULL;
	}

	kfree(ctrl->edid);
	ctrl->edid = NULL;

	mutex_destroy(&ctrl->dev_mutex);
}