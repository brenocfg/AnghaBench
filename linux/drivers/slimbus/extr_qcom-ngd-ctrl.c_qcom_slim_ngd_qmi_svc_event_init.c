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
struct qcom_slim_ngd_qmi {int /*<<< orphan*/  svc_event_hdl; } ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; struct qcom_slim_ngd_qmi qmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIMBUS_QMI_INS_ID ; 
 int /*<<< orphan*/  SLIMBUS_QMI_SVC_ID ; 
 int /*<<< orphan*/  SLIMBUS_QMI_SVC_V1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  qcom_slim_ngd_qmi_svc_event_ops ; 
 int qmi_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qmi_handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_slim_ngd_qmi_svc_event_init(struct qcom_slim_ngd_ctrl *ctrl)
{
	struct qcom_slim_ngd_qmi *qmi = &ctrl->qmi;
	int ret;

	ret = qmi_handle_init(&qmi->svc_event_hdl, 0,
				&qcom_slim_ngd_qmi_svc_event_ops, NULL);
	if (ret < 0) {
		dev_err(ctrl->dev, "qmi_handle_init failed: %d\n", ret);
		return ret;
	}

	ret = qmi_add_lookup(&qmi->svc_event_hdl, SLIMBUS_QMI_SVC_ID,
			SLIMBUS_QMI_SVC_V1, SLIMBUS_QMI_INS_ID);
	if (ret < 0) {
		dev_err(ctrl->dev, "qmi_add_lookup failed: %d\n", ret);
		qmi_handle_release(&qmi->svc_event_hdl);
	}
	return ret;
}