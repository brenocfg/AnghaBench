#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ result; int error; } ;
struct wlfw_msa_info_resp_msg_v01 {int mem_region_info_len; TYPE_2__* mem_region_info; TYPE_1__ resp; } ;
struct wlfw_msa_info_req_msg_v01 {int /*<<< orphan*/  size; int /*<<< orphan*/  msa_addr; } ;
struct qmi_txn {int dummy; } ;
struct ath10k_qmi {int nr_mem_region; TYPE_3__* mem_region; int /*<<< orphan*/  qmi_hdl; int /*<<< orphan*/  msa_mem_size; int /*<<< orphan*/  msa_pa; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  secure; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  secure_flag; int /*<<< orphan*/  size; int /*<<< orphan*/  region_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_QMI ; 
 int ATH10K_QMI_TIMEOUT ; 
 int EINVAL ; 
 int HZ ; 
 scalar_t__ QMI_RESULT_SUCCESS_V01 ; 
 int QMI_WLFW_MAX_MEM_REG_V01 ; 
 int /*<<< orphan*/  QMI_WLFW_MSA_INFO_REQ_V01 ; 
 int /*<<< orphan*/  WLFW_MSA_INFO_REQ_MSG_V01_MAX_MSG_LEN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int qmi_send_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlfw_msa_info_req_msg_v01*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,struct wlfw_msa_info_resp_msg_v01*) ; 
 int qmi_txn_wait (struct qmi_txn*,int) ; 
 int /*<<< orphan*/  wlfw_msa_info_req_msg_v01_ei ; 
 int /*<<< orphan*/  wlfw_msa_info_resp_msg_v01_ei ; 

__attribute__((used)) static int ath10k_qmi_msa_mem_info_send_sync_msg(struct ath10k_qmi *qmi)
{
	struct wlfw_msa_info_resp_msg_v01 resp = {};
	struct wlfw_msa_info_req_msg_v01 req = {};
	struct ath10k *ar = qmi->ar;
	struct qmi_txn txn;
	int ret;
	int i;

	req.msa_addr = qmi->msa_pa;
	req.size = qmi->msa_mem_size;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_msa_info_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&qmi->qmi_hdl, NULL, &txn,
			       QMI_WLFW_MSA_INFO_REQ_V01,
			       WLFW_MSA_INFO_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_msa_info_req_msg_v01_ei, &req);
	if (ret < 0) {
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send msa mem info req: %d\n", ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (ret < 0)
		goto out;

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath10k_err(ar, "msa info req rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

	if (resp.mem_region_info_len > QMI_WLFW_MAX_MEM_REG_V01) {
		ath10k_err(ar, "invalid memory region length received: %d\n",
			   resp.mem_region_info_len);
		ret = -EINVAL;
		goto out;
	}

	qmi->nr_mem_region = resp.mem_region_info_len;
	for (i = 0; i < resp.mem_region_info_len; i++) {
		qmi->mem_region[i].addr = resp.mem_region_info[i].region_addr;
		qmi->mem_region[i].size = resp.mem_region_info[i].size;
		qmi->mem_region[i].secure = resp.mem_region_info[i].secure_flag;
		ath10k_dbg(ar, ATH10K_DBG_QMI,
			   "qmi msa mem region %d addr 0x%pa size 0x%x flag 0x%08x\n",
			   i, &qmi->mem_region[i].addr,
			   qmi->mem_region[i].size,
			   qmi->mem_region[i].secure);
	}

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi msa mem info request completed\n");
	return 0;

out:
	return ret;
}