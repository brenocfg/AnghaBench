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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {scalar_t__ reply_address; } ;
struct TYPE_8__ {TYPE_2__ first_tlv; } ;
struct TYPE_9__ {int type; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {scalar_t__ reply_address; TYPE_4__ tl; int /*<<< orphan*/  padding; } ;
struct qed_iov_vf_mbx {int b_pending_msg; TYPE_5__ first_tlv; TYPE_1__* req_virt; } ;
struct qed_vf_info {int /*<<< orphan*/  abs_vf_id; TYPE_3__ acquire; int /*<<< orphan*/  b_malicious; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_6__ {TYPE_5__ first_tlv; } ;

/* Variables and functions */
#define  CHANNEL_TLV_ACQUIRE 144 
#define  CHANNEL_TLV_BULLETIN_UPDATE_MAC 143 
#define  CHANNEL_TLV_CLOSE 142 
#define  CHANNEL_TLV_COALESCE_READ 141 
#define  CHANNEL_TLV_COALESCE_UPDATE 140 
#define  CHANNEL_TLV_INT_CLEANUP 139 
#define  CHANNEL_TLV_RELEASE 138 
#define  CHANNEL_TLV_START_RXQ 137 
#define  CHANNEL_TLV_START_TXQ 136 
#define  CHANNEL_TLV_STOP_RXQS 135 
#define  CHANNEL_TLV_STOP_TXQS 134 
#define  CHANNEL_TLV_UCAST_FILTER 133 
#define  CHANNEL_TLV_UPDATE_RXQ 132 
#define  CHANNEL_TLV_UPDATE_TUNN_PARAM 131 
#define  CHANNEL_TLV_VPORT_START 130 
#define  CHANNEL_TLV_VPORT_TEARDOWN 129 
#define  CHANNEL_TLV_VPORT_UPDATE 128 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PFVF_STATUS_MALICIOUS ; 
 int /*<<< orphan*/  PFVF_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_iov_tlv_supported (int) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_acquire (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_close (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_int_cleanup (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_release (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_start_rxq (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_start_txq (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_start_vport (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_stop_rxqs (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_stop_txqs (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_stop_vport (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_ucast_filter (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_update_rxqs (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_update_tunn_param (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_vport_update (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_pf_bulletin_update_mac (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_pf_get_coalesce (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 int /*<<< orphan*/  qed_iov_vf_pf_set_coalesce (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 

__attribute__((used)) static void qed_iov_process_mbx_req(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt, int vfid)
{
	struct qed_iov_vf_mbx *mbx;
	struct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	if (!p_vf)
		return;

	mbx = &p_vf->vf_mbx;

	/* qed_iov_process_mbx_request */
	if (!mbx->b_pending_msg) {
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: Trying to process mailbox message when none is pending\n",
			  p_vf->abs_vf_id);
		return;
	}
	mbx->b_pending_msg = false;

	mbx->first_tlv = mbx->req_virt->first_tlv;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "VF[%02x]: Processing mailbox message [type %04x]\n",
		   p_vf->abs_vf_id, mbx->first_tlv.tl.type);

	/* check if tlv type is known */
	if (qed_iov_tlv_supported(mbx->first_tlv.tl.type) &&
	    !p_vf->b_malicious) {
		switch (mbx->first_tlv.tl.type) {
		case CHANNEL_TLV_ACQUIRE:
			qed_iov_vf_mbx_acquire(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_START:
			qed_iov_vf_mbx_start_vport(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_TEARDOWN:
			qed_iov_vf_mbx_stop_vport(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_START_RXQ:
			qed_iov_vf_mbx_start_rxq(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_START_TXQ:
			qed_iov_vf_mbx_start_txq(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_STOP_RXQS:
			qed_iov_vf_mbx_stop_rxqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_STOP_TXQS:
			qed_iov_vf_mbx_stop_txqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UPDATE_RXQ:
			qed_iov_vf_mbx_update_rxqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_UPDATE:
			qed_iov_vf_mbx_vport_update(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UCAST_FILTER:
			qed_iov_vf_mbx_ucast_filter(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_CLOSE:
			qed_iov_vf_mbx_close(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_INT_CLEANUP:
			qed_iov_vf_mbx_int_cleanup(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_RELEASE:
			qed_iov_vf_mbx_release(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UPDATE_TUNN_PARAM:
			qed_iov_vf_mbx_update_tunn_param(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_COALESCE_UPDATE:
			qed_iov_vf_pf_set_coalesce(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_COALESCE_READ:
			qed_iov_vf_pf_get_coalesce(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_BULLETIN_UPDATE_MAC:
			qed_iov_vf_pf_bulletin_update_mac(p_hwfn, p_ptt, p_vf);
			break;
		}
	} else if (qed_iov_tlv_supported(mbx->first_tlv.tl.type)) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF [%02x] - considered malicious; Ignoring TLV [%04x]\n",
			   p_vf->abs_vf_id, mbx->first_tlv.tl.type);

		qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
				     mbx->first_tlv.tl.type,
				     sizeof(struct pfvf_def_resp_tlv),
				     PFVF_STATUS_MALICIOUS);
	} else {
		/* unknown TLV - this may belong to a VF driver from the future
		 * - a version written after this PF driver was written, which
		 * supports features unknown as of yet. Too bad since we don't
		 * support them. Or this may be because someone wrote a crappy
		 * VF driver and is sending garbage over the channel.
		 */
		DP_NOTICE(p_hwfn,
			  "VF[%02x]: unknown TLV. type %04x length %04x padding %08x reply address %llu\n",
			  p_vf->abs_vf_id,
			  mbx->first_tlv.tl.type,
			  mbx->first_tlv.tl.length,
			  mbx->first_tlv.padding, mbx->first_tlv.reply_address);

		/* Try replying in case reply address matches the acquisition's
		 * posted address.
		 */
		if (p_vf->acquire.first_tlv.reply_address &&
		    (mbx->first_tlv.reply_address ==
		     p_vf->acquire.first_tlv.reply_address)) {
			qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
					     mbx->first_tlv.tl.type,
					     sizeof(struct pfvf_def_resp_tlv),
					     PFVF_STATUS_NOT_SUPPORTED);
		} else {
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%02x]: Can't respond to TLV - no valid reply address\n",
				   p_vf->abs_vf_id);
		}
	}
}