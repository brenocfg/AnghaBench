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
struct vfpf_set_q_filters_tlv {int /*<<< orphan*/  vf_qid; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {struct vfpf_set_q_filters_tlv set_q_filters; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnx2x_filters_validate_mac (struct bnx2x*,struct bnx2x_virtf*,struct vfpf_set_q_filters_tlv*) ; 
 int bnx2x_filters_validate_vlan (struct bnx2x*,struct bnx2x_virtf*,struct vfpf_set_q_filters_tlv*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_dp_q_filters (struct bnx2x*,int /*<<< orphan*/ ,struct vfpf_set_q_filters_tlv*) ; 
 int bnx2x_vf_mbx_qfilters (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*,int) ; 

__attribute__((used)) static void bnx2x_vf_mbx_set_q_filters(struct bnx2x *bp,
				       struct bnx2x_virtf *vf,
				       struct bnx2x_vf_mbx *mbx)
{
	struct vfpf_set_q_filters_tlv *filters = &mbx->msg->req.set_q_filters;
	int rc;

	rc = bnx2x_filters_validate_mac(bp, vf, filters);
	if (rc)
		goto response;

	rc = bnx2x_filters_validate_vlan(bp, vf, filters);
	if (rc)
		goto response;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_FILTERS: queue[%d]\n",
	   vf->abs_vfid,
	   filters->vf_qid);

	/* print q_filter message */
	bnx2x_vf_mbx_dp_q_filters(bp, BNX2X_MSG_IOV, filters);

	rc = bnx2x_vf_mbx_qfilters(bp, vf);
response:
	bnx2x_vf_mbx_resp(bp, vf, rc);
}