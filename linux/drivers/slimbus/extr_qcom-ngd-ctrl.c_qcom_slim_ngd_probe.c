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
struct TYPE_2__ {struct device* dev; } ;
struct qcom_slim_ngd_ctrl {scalar_t__ mwq; int /*<<< orphan*/  qmi; int /*<<< orphan*/  m_work; TYPE_1__ ctrl; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCOM_SLIM_NGD_AUTOSUSPEND ; 
 scalar_t__ create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct qcom_slim_ngd_ctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  qcom_slim_ngd_master_worker ; 
 int /*<<< orphan*/  qcom_slim_ngd_qmi_svc_event_deinit (int /*<<< orphan*/ *) ; 
 int qcom_slim_ngd_qmi_svc_event_init (struct qcom_slim_ngd_ctrl*) ; 

__attribute__((used)) static int qcom_slim_ngd_probe(struct platform_device *pdev)
{
	struct qcom_slim_ngd_ctrl *ctrl = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int ret;

	ctrl->ctrl.dev = dev;

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, QCOM_SLIM_NGD_AUTOSUSPEND);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);
	pm_runtime_get_noresume(dev);
	ret = qcom_slim_ngd_qmi_svc_event_init(ctrl);
	if (ret) {
		dev_err(&pdev->dev, "QMI service registration failed:%d", ret);
		return ret;
	}

	INIT_WORK(&ctrl->m_work, qcom_slim_ngd_master_worker);
	ctrl->mwq = create_singlethread_workqueue("ngd_master");
	if (!ctrl->mwq) {
		dev_err(&pdev->dev, "Failed to start master worker\n");
		ret = -ENOMEM;
		goto wq_err;
	}

	return 0;
wq_err:
	qcom_slim_ngd_qmi_svc_event_deinit(&ctrl->qmi);
	if (ctrl->mwq)
		destroy_workqueue(ctrl->mwq);

	return ret;
}