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
typedef  int /*<<< orphan*/  u8 ;
struct qed_vf_info {int spoof_chk; int b_malicious; int /*<<< orphan*/  shadow_config; scalar_t__ configured_features; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  abs_vf_id; int /*<<< orphan*/  vport_instance; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_def_resp_tlv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_TEARDOWN ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFVF_STATUS_FAILURE ; 
 int /*<<< orphan*/  PFVF_STATUS_MALICIOUS ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_iov_validate_active_rxq (struct qed_hwfn*,struct qed_vf_info*) ; 
 scalar_t__ qed_iov_validate_active_txq (struct qed_hwfn*,struct qed_vf_info*) ; 
 int qed_sp_vport_stop (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_iov_vf_mbx_stop_vport(struct qed_hwfn *p_hwfn,
				      struct qed_ptt *p_ptt,
				      struct qed_vf_info *vf)
{
	u8 status = PFVF_STATUS_SUCCESS;
	int rc;

	vf->vport_instance--;
	vf->spoof_chk = false;

	if ((qed_iov_validate_active_rxq(p_hwfn, vf)) ||
	    (qed_iov_validate_active_txq(p_hwfn, vf))) {
		vf->b_malicious = true;
		DP_NOTICE(p_hwfn,
			  "VF [%02x] - considered malicious; Unable to stop RX/TX queues\n",
			  vf->abs_vf_id);
		status = PFVF_STATUS_MALICIOUS;
		goto out;
	}

	rc = qed_sp_vport_stop(p_hwfn, vf->opaque_fid, vf->vport_id);
	if (rc) {
		DP_ERR(p_hwfn, "qed_iov_vf_mbx_stop_vport returned error %d\n",
		       rc);
		status = PFVF_STATUS_FAILURE;
	}

	/* Forget the configuration on the vport */
	vf->configured_features = 0;
	memset(&vf->shadow_config, 0, sizeof(vf->shadow_config));

out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_VPORT_TEARDOWN,
			     sizeof(struct pfvf_def_resp_tlv), status);
}