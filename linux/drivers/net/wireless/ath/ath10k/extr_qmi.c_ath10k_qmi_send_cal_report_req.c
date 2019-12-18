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
struct TYPE_4__ {scalar_t__ result; int error; } ;
struct wlfw_cal_report_resp_msg_v01 {TYPE_2__ resp; } ;
struct wlfw_cal_report_req_msg_v01 {int meta_data_len; int /*<<< orphan*/ * meta_data; } ;
struct qmi_txn {int dummy; } ;
struct ath10k_qmi {int /*<<< orphan*/  qmi_hdl; TYPE_1__* cal_data; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cal_id; scalar_t__ data; scalar_t__ total_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_QMI ; 
 int ATH10K_QMI_TIMEOUT ; 
 int EINVAL ; 
 int HZ ; 
 scalar_t__ QMI_RESULT_SUCCESS_V01 ; 
 int /*<<< orphan*/  QMI_WLFW_CAL_REPORT_REQ_V01 ; 
 int QMI_WLFW_MAX_NUM_CAL_V01 ; 
 int /*<<< orphan*/  WLFW_CAL_REPORT_REQ_MSG_V01_MAX_MSG_LEN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int qmi_send_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlfw_cal_report_req_msg_v01*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,struct wlfw_cal_report_resp_msg_v01*) ; 
 int qmi_txn_wait (struct qmi_txn*,int) ; 
 int /*<<< orphan*/  wlfw_cal_report_req_msg_v01_ei ; 
 int /*<<< orphan*/  wlfw_cal_report_resp_msg_v01_ei ; 

__attribute__((used)) static int ath10k_qmi_send_cal_report_req(struct ath10k_qmi *qmi)
{
	struct wlfw_cal_report_resp_msg_v01 resp = {};
	struct wlfw_cal_report_req_msg_v01 req = {};
	struct ath10k *ar = qmi->ar;
	struct qmi_txn txn;
	int i, j = 0;
	int ret;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn, wlfw_cal_report_resp_msg_v01_ei,
			   &resp);
	if (ret < 0)
		goto out;

	for (i = 0; i < QMI_WLFW_MAX_NUM_CAL_V01; i++) {
		if (qmi->cal_data[i].total_size &&
		    qmi->cal_data[i].data) {
			req.meta_data[j] = qmi->cal_data[i].cal_id;
			j++;
		}
	}
	req.meta_data_len = j;

	ret = qmi_send_request(&qmi->qmi_hdl, NULL, &txn,
			       QMI_WLFW_CAL_REPORT_REQ_V01,
			       WLFW_CAL_REPORT_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_cal_report_req_msg_v01_ei, &req);
	if (ret < 0) {
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send calibration request: %d\n", ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (ret < 0)
		goto out;

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath10k_err(ar, "calibration request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi cal report request completed\n");
	return 0;

out:
	return ret;
}