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
struct TYPE_2__ {int /*<<< orphan*/  qmi_comp; } ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  dev; TYPE_1__ qmi; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_slim_ngd_runtime_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_slim_qmi_exit (struct qcom_slim_ngd_ctrl*) ; 
 int qcom_slim_qmi_init (struct qcom_slim_ngd_ctrl*,int) ; 
 int slim_register_controller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_unregister_controller (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_ngd_enable(struct qcom_slim_ngd_ctrl *ctrl, bool enable)
{
	if (enable) {
		int ret = qcom_slim_qmi_init(ctrl, false);

		if (ret) {
			dev_err(ctrl->dev, "qmi init fail, ret:%d, state:%d\n",
				ret, ctrl->state);
			return ret;
		}
		/* controller state should be in sync with framework state */
		complete(&ctrl->qmi.qmi_comp);
		if (!pm_runtime_enabled(ctrl->dev) ||
				!pm_runtime_suspended(ctrl->dev))
			qcom_slim_ngd_runtime_resume(ctrl->dev);
		else
			pm_runtime_resume(ctrl->dev);
		pm_runtime_mark_last_busy(ctrl->dev);
		pm_runtime_put(ctrl->dev);

		ret = slim_register_controller(&ctrl->ctrl);
		if (ret) {
			dev_err(ctrl->dev, "error adding slim controller\n");
			return ret;
		}

		dev_info(ctrl->dev, "SLIM controller Registered\n");
	} else {
		qcom_slim_qmi_exit(ctrl);
		slim_unregister_controller(&ctrl->ctrl);
	}

	return 0;
}