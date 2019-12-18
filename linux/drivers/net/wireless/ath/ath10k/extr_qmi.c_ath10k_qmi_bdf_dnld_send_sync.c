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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ result; int /*<<< orphan*/  error; } ;
struct wlfw_bdf_download_resp_msg_v01 {TYPE_2__ resp; } ;
struct wlfw_bdf_download_req_msg_v01 {int valid; int file_id_valid; int total_size_valid; unsigned int total_size; int seg_id_valid; int data_valid; int end_valid; unsigned int data_len; int end; int /*<<< orphan*/  seg_id; int /*<<< orphan*/  data; scalar_t__ file_id; } ;
struct qmi_txn {int dummy; } ;
struct ath10k_qmi {int /*<<< orphan*/  qmi_hdl; struct ath10k* ar; } ;
struct TYPE_3__ {unsigned int board_len; int /*<<< orphan*/ * board_data; } ;
struct ath10k {TYPE_1__ normal_mode_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_QMI ; 
 int ATH10K_QMI_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 scalar_t__ QMI_RESULT_SUCCESS_V01 ; 
 int /*<<< orphan*/  QMI_WLFW_BDF_DOWNLOAD_REQ_V01 ; 
 unsigned int QMI_WLFW_MAX_DATA_SIZE_V01 ; 
 int /*<<< orphan*/  WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wlfw_bdf_download_req_msg_v01*) ; 
 struct wlfw_bdf_download_req_msg_v01* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int qmi_send_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlfw_bdf_download_req_msg_v01*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,struct wlfw_bdf_download_resp_msg_v01*) ; 
 int qmi_txn_wait (struct qmi_txn*,int) ; 
 int /*<<< orphan*/  wlfw_bdf_download_req_msg_v01_ei ; 
 int /*<<< orphan*/  wlfw_bdf_download_resp_msg_v01_ei ; 

__attribute__((used)) static int ath10k_qmi_bdf_dnld_send_sync(struct ath10k_qmi *qmi)
{
	struct wlfw_bdf_download_resp_msg_v01 resp = {};
	struct wlfw_bdf_download_req_msg_v01 *req;
	struct ath10k *ar = qmi->ar;
	unsigned int remaining;
	struct qmi_txn txn;
	const u8 *temp;
	int ret;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	temp = ar->normal_mode_fw.board_data;
	remaining = ar->normal_mode_fw.board_len;

	while (remaining) {
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = 0;
		req->total_size_valid = 1;
		req->total_size = ar->normal_mode_fw.board_len;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->end_valid = 1;

		if (remaining > QMI_WLFW_MAX_DATA_SIZE_V01) {
			req->data_len = QMI_WLFW_MAX_DATA_SIZE_V01;
		} else {
			req->data_len = remaining;
			req->end = 1;
		}

		memcpy(req->data, temp, req->data_len);

		ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
				   wlfw_bdf_download_resp_msg_v01_ei,
				   &resp);
		if (ret < 0)
			goto out;

		ret = qmi_send_request(&qmi->qmi_hdl, NULL, &txn,
				       QMI_WLFW_BDF_DOWNLOAD_REQ_V01,
				       WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN,
				       wlfw_bdf_download_req_msg_v01_ei, req);
		if (ret < 0) {
			qmi_txn_cancel(&txn);
			goto out;
		}

		ret = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);

		if (ret < 0)
			goto out;

		if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
			ath10k_err(ar, "failed to download board data file: %d\n",
				   resp.resp.error);
			ret = -EINVAL;
			goto out;
		}

		remaining -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
	}

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi bdf download request completed\n");

	kfree(req);
	return 0;

out:
	kfree(req);
	return ret;
}