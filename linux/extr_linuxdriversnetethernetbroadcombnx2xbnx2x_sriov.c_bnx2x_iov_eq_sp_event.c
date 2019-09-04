#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int vf_id; int err_id; } ;
struct TYPE_12__ {int vf_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  echo; } ;
struct TYPE_10__ {int /*<<< orphan*/  cid; } ;
struct TYPE_14__ {TYPE_4__ malicious_vf_event; TYPE_3__ vf_flr_event; TYPE_2__ eth_event; TYPE_1__ cfc_del_event; } ;
struct TYPE_15__ {int opcode; TYPE_5__ data; } ;
union event_ring_elem {TYPE_6__ message; } ;
typedef  int u8 ;
typedef  int u16 ;
struct bnx2x_virtf {int malicious; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* complete_cmd ) (struct bnx2x*,TYPE_8__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {TYPE_8__ sp_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,int) ; 
 int BNX2X_MAX_NUM_OF_VFS ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_Q_CMD_CFC_DEL ; 
 int BNX2X_VF_CID_WND ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
#define  EVENT_RING_OPCODE_CFC_DEL 134 
#define  EVENT_RING_OPCODE_CLASSIFICATION_RULES 133 
#define  EVENT_RING_OPCODE_FILTERS_RULES 132 
#define  EVENT_RING_OPCODE_MALICIOUS_VF 131 
#define  EVENT_RING_OPCODE_MULTICAST_RULES 130 
#define  EVENT_RING_OPCODE_RSS_UPDATE_RULES 129 
#define  EVENT_RING_OPCODE_VF_FLR 128 
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 
 int SW_CID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_iov_is_vf_cid (struct bnx2x*,int) ; 
 struct bnx2x_virtf* bnx2x_vf_by_abs_fid (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_vf_handle_classification_eqe (struct bnx2x*,TYPE_7__*,union event_ring_elem*) ; 
 int /*<<< orphan*/  bnx2x_vf_handle_filters_eqe (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_handle_mcast_eqe (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_handle_rss_update_eqe (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* vfq_get (struct bnx2x_virtf*,int) ; 

int bnx2x_iov_eq_sp_event(struct bnx2x *bp, union event_ring_elem *elem)
{
	struct bnx2x_virtf *vf;
	int qidx = 0, abs_vfid;
	u8 opcode;
	u16 cid = 0xffff;

	if (!IS_SRIOV(bp))
		return 1;

	/* first get the cid - the only events we handle here are cfc-delete
	 * and set-mac completion
	 */
	opcode = elem->message.opcode;

	switch (opcode) {
	case EVENT_RING_OPCODE_CFC_DEL:
		cid = SW_CID(elem->message.data.cfc_del_event.cid);
		DP(BNX2X_MSG_IOV, "checking cfc-del comp cid=%d\n", cid);
		break;
	case EVENT_RING_OPCODE_CLASSIFICATION_RULES:
	case EVENT_RING_OPCODE_MULTICAST_RULES:
	case EVENT_RING_OPCODE_FILTERS_RULES:
	case EVENT_RING_OPCODE_RSS_UPDATE_RULES:
		cid = SW_CID(elem->message.data.eth_event.echo);
		DP(BNX2X_MSG_IOV, "checking filtering comp cid=%d\n", cid);
		break;
	case EVENT_RING_OPCODE_VF_FLR:
		abs_vfid = elem->message.data.vf_flr_event.vf_id;
		DP(BNX2X_MSG_IOV, "Got VF FLR notification abs_vfid=%d\n",
		   abs_vfid);
		goto get_vf;
	case EVENT_RING_OPCODE_MALICIOUS_VF:
		abs_vfid = elem->message.data.malicious_vf_event.vf_id;
		BNX2X_ERR("Got VF MALICIOUS notification abs_vfid=%d err_id=0x%x\n",
			  abs_vfid,
			  elem->message.data.malicious_vf_event.err_id);
		goto get_vf;
	default:
		return 1;
	}

	/* check if the cid is the VF range */
	if (!bnx2x_iov_is_vf_cid(bp, cid)) {
		DP(BNX2X_MSG_IOV, "cid is outside vf range: %d\n", cid);
		return 1;
	}

	/* extract vf and rxq index from vf_cid - relies on the following:
	 * 1. vfid on cid reflects the true abs_vfid
	 * 2. The max number of VFs (per path) is 64
	 */
	qidx = cid & ((1 << BNX2X_VF_CID_WND)-1);
	abs_vfid = (cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
get_vf:
	vf = bnx2x_vf_by_abs_fid(bp, abs_vfid);

	if (!vf) {
		BNX2X_ERR("EQ completion for unknown VF, cid %d, abs_vfid %d\n",
			  cid, abs_vfid);
		return 0;
	}

	switch (opcode) {
	case EVENT_RING_OPCODE_CFC_DEL:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] cfc delete ramrod\n",
		   vf->abs_vfid, qidx);
		vfq_get(vf, qidx)->sp_obj.complete_cmd(bp,
						       &vfq_get(vf,
								qidx)->sp_obj,
						       BNX2X_Q_CMD_CFC_DEL);
		break;
	case EVENT_RING_OPCODE_CLASSIFICATION_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mac/vlan ramrod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handle_classification_eqe(bp, vfq_get(vf, qidx), elem);
		break;
	case EVENT_RING_OPCODE_MULTICAST_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mcast ramrod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handle_mcast_eqe(bp, vf);
		break;
	case EVENT_RING_OPCODE_FILTERS_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set rx-mode ramrod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handle_filters_eqe(bp, vf);
		break;
	case EVENT_RING_OPCODE_RSS_UPDATE_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] RSS update ramrod\n",
		   vf->abs_vfid, qidx);
		bnx2x_vf_handle_rss_update_eqe(bp, vf);
		/* fall through */
	case EVENT_RING_OPCODE_VF_FLR:
		/* Do nothing for now */
		return 0;
	case EVENT_RING_OPCODE_MALICIOUS_VF:
		vf->malicious = true;
		return 0;
	}

	return 0;
}