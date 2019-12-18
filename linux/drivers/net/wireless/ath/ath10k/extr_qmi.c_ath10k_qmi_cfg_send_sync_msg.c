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
typedef  size_t u32 ;
struct TYPE_10__ {scalar_t__ result; int error; } ;
struct wlfw_wlan_cfg_resp_msg_v01 {TYPE_5__ resp; } ;
struct wlfw_wlan_cfg_req_msg_v01 {int tgt_cfg_valid; scalar_t__ tgt_cfg_len; int svc_cfg_valid; scalar_t__ svc_cfg_len; int shadow_reg_valid; scalar_t__ shadow_reg_len; int /*<<< orphan*/  shadow_reg; TYPE_3__* svc_cfg; TYPE_1__* tgt_cfg; scalar_t__ host_version_valid; } ;
struct wlfw_shadow_reg_cfg_s_v01 {int dummy; } ;
struct qmi_txn {int dummy; } ;
struct ath10k_snoc {struct ath10k_qmi* qmi; } ;
struct ath10k_qmi_wlan_enable_cfg {scalar_t__ num_ce_tgt_cfg; scalar_t__ num_ce_svc_pipe_cfg; scalar_t__ num_shadow_reg_cfg; int /*<<< orphan*/  shadow_reg_cfg; TYPE_4__* ce_svc_cfg; TYPE_2__* ce_tgt_cfg; } ;
struct ath10k_qmi {int /*<<< orphan*/  qmi_hdl; } ;
struct ath10k {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  pipe_num; int /*<<< orphan*/  pipe_dir; int /*<<< orphan*/  service_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  pipe_num; int /*<<< orphan*/  pipe_dir; int /*<<< orphan*/  service_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  nbytes_max; int /*<<< orphan*/  nentries; int /*<<< orphan*/  pipe_dir; int /*<<< orphan*/  pipe_num; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  nbytes_max; int /*<<< orphan*/  nentries; int /*<<< orphan*/  pipe_dir; int /*<<< orphan*/  pipe_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_QMI ; 
 int ATH10K_QMI_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 scalar_t__ QMI_RESULT_SUCCESS_V01 ; 
 scalar_t__ QMI_WLFW_MAX_NUM_CE_V01 ; 
 scalar_t__ QMI_WLFW_MAX_NUM_SHADOW_REG_V01 ; 
 scalar_t__ QMI_WLFW_MAX_NUM_SVC_V01 ; 
 int /*<<< orphan*/  QMI_WLFW_WLAN_CFG_REQ_V01 ; 
 int /*<<< orphan*/  WLFW_WLAN_CFG_REQ_MSG_V01_MAX_MSG_LEN ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  kfree (struct wlfw_wlan_cfg_req_msg_v01*) ; 
 struct wlfw_wlan_cfg_req_msg_v01* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qmi_send_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlfw_wlan_cfg_req_msg_v01*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,struct wlfw_wlan_cfg_resp_msg_v01*) ; 
 int qmi_txn_wait (struct qmi_txn*,int) ; 
 int /*<<< orphan*/  wlfw_wlan_cfg_req_msg_v01_ei ; 
 int /*<<< orphan*/  wlfw_wlan_cfg_resp_msg_v01_ei ; 

__attribute__((used)) static int
ath10k_qmi_cfg_send_sync_msg(struct ath10k *ar,
			     struct ath10k_qmi_wlan_enable_cfg *config,
			     const char *version)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_qmi *qmi = ar_snoc->qmi;
	struct wlfw_wlan_cfg_resp_msg_v01 resp = {};
	struct wlfw_wlan_cfg_req_msg_v01 *req;
	struct qmi_txn txn;
	int ret;
	u32 i;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	ret = qmi_txn_init(&qmi->qmi_hdl, &txn,
			   wlfw_wlan_cfg_resp_msg_v01_ei,
			   &resp);
	if (ret < 0)
		goto out;

	req->host_version_valid = 0;

	req->tgt_cfg_valid = 1;
	if (config->num_ce_tgt_cfg > QMI_WLFW_MAX_NUM_CE_V01)
		req->tgt_cfg_len = QMI_WLFW_MAX_NUM_CE_V01;
	else
		req->tgt_cfg_len = config->num_ce_tgt_cfg;
	for (i = 0; i < req->tgt_cfg_len; i++) {
		req->tgt_cfg[i].pipe_num = config->ce_tgt_cfg[i].pipe_num;
		req->tgt_cfg[i].pipe_dir = config->ce_tgt_cfg[i].pipe_dir;
		req->tgt_cfg[i].nentries = config->ce_tgt_cfg[i].nentries;
		req->tgt_cfg[i].nbytes_max = config->ce_tgt_cfg[i].nbytes_max;
		req->tgt_cfg[i].flags = config->ce_tgt_cfg[i].flags;
	}

	req->svc_cfg_valid = 1;
	if (config->num_ce_svc_pipe_cfg > QMI_WLFW_MAX_NUM_SVC_V01)
		req->svc_cfg_len = QMI_WLFW_MAX_NUM_SVC_V01;
	else
		req->svc_cfg_len = config->num_ce_svc_pipe_cfg;
	for (i = 0; i < req->svc_cfg_len; i++) {
		req->svc_cfg[i].service_id = config->ce_svc_cfg[i].service_id;
		req->svc_cfg[i].pipe_dir = config->ce_svc_cfg[i].pipe_dir;
		req->svc_cfg[i].pipe_num = config->ce_svc_cfg[i].pipe_num;
	}

	req->shadow_reg_valid = 1;
	if (config->num_shadow_reg_cfg >
	    QMI_WLFW_MAX_NUM_SHADOW_REG_V01)
		req->shadow_reg_len = QMI_WLFW_MAX_NUM_SHADOW_REG_V01;
	else
		req->shadow_reg_len = config->num_shadow_reg_cfg;

	memcpy(req->shadow_reg, config->shadow_reg_cfg,
	       sizeof(struct wlfw_shadow_reg_cfg_s_v01) * req->shadow_reg_len);

	ret = qmi_send_request(&qmi->qmi_hdl, NULL, &txn,
			       QMI_WLFW_WLAN_CFG_REQ_V01,
			       WLFW_WLAN_CFG_REQ_MSG_V01_MAX_MSG_LEN,
			       wlfw_wlan_cfg_req_msg_v01_ei, req);
	if (ret < 0) {
		qmi_txn_cancel(&txn);
		ath10k_err(ar, "failed to send config request: %d\n", ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (ret < 0)
		goto out;

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath10k_err(ar, "config request rejected: %d\n", resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi config request completed\n");
	kfree(req);
	return 0;

out:
	kfree(req);
	return ret;
}