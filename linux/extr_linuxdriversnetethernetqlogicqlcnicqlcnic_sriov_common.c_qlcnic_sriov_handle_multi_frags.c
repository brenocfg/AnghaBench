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
typedef  scalar_t__ u8 ;
struct qlcnic_bc_trans {scalar_t__ curr_rsp_frag; scalar_t__ curr_req_frag; void* trans_state; TYPE_1__* req_hdr; TYPE_2__* rsp_hdr; } ;
struct TYPE_4__ {scalar_t__ num_frags; } ;
struct TYPE_3__ {scalar_t__ num_frags; } ;

/* Variables and functions */
 scalar_t__ QLC_BC_RESPONSE ; 
 void* QLC_END ; 
 void* QLC_INIT ; 
 void* QLC_WAIT_FOR_RESP ; 

__attribute__((used)) static void qlcnic_sriov_handle_multi_frags(struct qlcnic_bc_trans *trans,
					    u8 type)
{
	if (type == QLC_BC_RESPONSE) {
		trans->curr_rsp_frag++;
		if (trans->curr_rsp_frag < trans->rsp_hdr->num_frags)
			trans->trans_state = QLC_INIT;
		else
			trans->trans_state = QLC_END;
	} else {
		trans->curr_req_frag++;
		if (trans->curr_req_frag < trans->req_hdr->num_frags)
			trans->trans_state = QLC_INIT;
		else
			trans->trans_state = QLC_WAIT_FOR_RESP;
	}
}