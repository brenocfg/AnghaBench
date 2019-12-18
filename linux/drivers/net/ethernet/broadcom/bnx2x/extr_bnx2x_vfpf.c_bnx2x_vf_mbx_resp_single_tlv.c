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
typedef  scalar_t__ u16 ;
struct pfvf_general_resp_tlv {int dummy; } ;
struct pfvf_acquire_resp_tlv {int dummy; } ;
struct channel_list_end_tlv {int dummy; } ;
struct bnx2x_virtf {int /*<<< orphan*/  index; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ tl; } ;
struct bnx2x_vf_mbx {TYPE_3__* msg; TYPE_2__ first_tlv; } ;
struct bnx2x {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  resp; } ;

/* Variables and functions */
 struct bnx2x_vf_mbx* BP_VF_MBX (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHANNEL_TLV_ACQUIRE ; 
 scalar_t__ CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void bnx2x_vf_mbx_resp_single_tlv(struct bnx2x *bp,
					 struct bnx2x_virtf *vf)
{
	struct bnx2x_vf_mbx *mbx = BP_VF_MBX(bp, vf->index);
	u16 length, type;

	/* prepare response */
	type = mbx->first_tlv.tl.type;
	length = type == CHANNEL_TLV_ACQUIRE ?
		sizeof(struct pfvf_acquire_resp_tlv) :
		sizeof(struct pfvf_general_resp_tlv);
	bnx2x_add_tlv(bp, &mbx->msg->resp, 0, type, length);
	bnx2x_add_tlv(bp, &mbx->msg->resp, length, CHANNEL_TLV_LIST_END,
		      sizeof(struct channel_list_end_tlv));
}