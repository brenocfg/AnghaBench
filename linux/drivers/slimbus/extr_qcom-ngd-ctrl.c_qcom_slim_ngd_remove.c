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
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/ * ngd; scalar_t__ mwq; int /*<<< orphan*/  qmi; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct qcom_slim_ngd_ctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_slim_ngd_enable (struct qcom_slim_ngd_ctrl*,int) ; 
 int /*<<< orphan*/  qcom_slim_ngd_exit_dma (struct qcom_slim_ngd_ctrl*) ; 
 int /*<<< orphan*/  qcom_slim_ngd_qmi_svc_event_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_ngd_remove(struct platform_device *pdev)
{
	struct qcom_slim_ngd_ctrl *ctrl = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	qcom_slim_ngd_enable(ctrl, false);
	qcom_slim_ngd_exit_dma(ctrl);
	qcom_slim_ngd_qmi_svc_event_deinit(&ctrl->qmi);
	if (ctrl->mwq)
		destroy_workqueue(ctrl->mwq);

	kfree(ctrl->ngd);
	ctrl->ngd = NULL;
	return 0;
}