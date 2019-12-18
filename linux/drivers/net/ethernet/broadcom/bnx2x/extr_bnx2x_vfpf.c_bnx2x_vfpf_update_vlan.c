#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_23__ {int /*<<< orphan*/  length; } ;
struct TYPE_14__ {TYPE_9__ tl; } ;
struct vfpf_set_q_filters_tlv {int n_mac_vlan_filters; TYPE_11__ first_tlv; TYPE_8__* filters; int /*<<< orphan*/  vf_qid; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {scalar_t__ status; } ;
struct pfvf_general_resp_tlv {TYPE_10__ hdr; } ;
struct channel_list_end_tlv {int dummy; } ;
struct TYPE_20__ {int valid_bitmap; } ;
struct TYPE_21__ {TYPE_6__ content; } ;
struct TYPE_18__ {int pf_cap; } ;
struct TYPE_19__ {TYPE_4__ pfdev_info; } ;
struct bnx2x {int /*<<< orphan*/  vf2pf_mbox_mapping; TYPE_7__ shadow_bulletin; TYPE_5__ acquire_resp; TYPE_3__* vf2pf_mbox; } ;
struct TYPE_22__ {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {struct pfvf_general_resp_tlv general_resp; } ;
struct TYPE_15__ {struct vfpf_set_q_filters_tlv set_q_filters; } ;
struct TYPE_17__ {TYPE_2__ resp; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_SET_Q_FILTERS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int PFVF_CAP_VLAN_FILTER ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  VFPF_Q_FILTER_SET ; 
 int /*<<< orphan*/  VFPF_Q_FILTER_VLAN_TAG_VALID ; 
 int /*<<< orphan*/  VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED ; 
 int VLAN_VALID ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,struct vfpf_set_q_filters_tlv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_dp_tlv_list (struct bnx2x*,struct vfpf_set_q_filters_tlv*) ; 
 int /*<<< orphan*/  bnx2x_sample_bulletin (struct bnx2x*) ; 
 int bnx2x_send_msg2pf (struct bnx2x*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfpf_finalize (struct bnx2x*,TYPE_11__*) ; 
 int /*<<< orphan*/  bnx2x_vfpf_prep (struct bnx2x*,TYPE_11__*,int /*<<< orphan*/ ,int) ; 

int bnx2x_vfpf_update_vlan(struct bnx2x *bp, u16 vid, u8 vf_qid, bool add)
{
	struct vfpf_set_q_filters_tlv *req = &bp->vf2pf_mbox->req.set_q_filters;
	struct pfvf_general_resp_tlv *resp = &bp->vf2pf_mbox->resp.general_resp;
	int rc = 0;

	if (!(bp->acquire_resp.pfdev_info.pf_cap & PFVF_CAP_VLAN_FILTER)) {
		DP(BNX2X_MSG_IOV, "HV does not support vlan filtering\n");
		return 0;
	}

	/* clear mailbox and prep first tlv */
	bnx2x_vfpf_prep(bp, &req->first_tlv, CHANNEL_TLV_SET_Q_FILTERS,
			sizeof(*req));

	req->flags = VFPF_SET_Q_FILTERS_MAC_VLAN_CHANGED;
	req->vf_qid = vf_qid;
	req->n_mac_vlan_filters = 1;

	req->filters[0].flags = VFPF_Q_FILTER_VLAN_TAG_VALID;

	if (add)
		req->filters[0].flags |= VFPF_Q_FILTER_SET;

	/* sample bulletin board for hypervisor vlan */
	bnx2x_sample_bulletin(bp);

	if (bp->shadow_bulletin.content.valid_bitmap & 1 << VLAN_VALID) {
		BNX2X_ERR("Hypervisor will decline the request, avoiding\n");
		rc = -EINVAL;
		goto out;
	}

	req->filters[0].vlan_tag = vid;

	/* add list termination tlv */
	bnx2x_add_tlv(bp, req, req->first_tlv.tl.length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));

	/* output tlvs list */
	bnx2x_dp_tlv_list(bp, req);

	/* send message to pf */
	rc = bnx2x_send_msg2pf(bp, &resp->hdr.status, bp->vf2pf_mbox_mapping);
	if (rc) {
		BNX2X_ERR("failed to send message to pf. rc was %d\n", rc);
		goto out;
	}

	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		BNX2X_ERR("vfpf %s VLAN %d failed\n", add ? "add" : "del",
			  vid);
		rc = -EINVAL;
	}
out:
	bnx2x_vfpf_finalize(bp, &req->first_tlv);

	return rc;
}