#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ term_flags; } ;
struct i40iw_qp {int hw_iwarp_state; int /*<<< orphan*/  iwdev; TYPE_1__ sc_qp; } ;
struct i40iw_modify_qp_info {int next_iwarp_state; int remove_hash_idx; int cq_num_valid; int arp_cache_idx_valid; int dont_send_term; int dont_send_fin; int termlen; int reset_tcp_conn; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int I40IWQP_TERM_SEND_FIN_ONLY ; 
 int I40IWQP_TERM_SEND_TERM_ONLY ; 
 int I40IW_QP_STATE_ERROR ; 
 int /*<<< orphan*/  i40iw_hw_modify_qp (int /*<<< orphan*/ ,struct i40iw_qp*,struct i40iw_modify_qp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40iw_modify_qp_info*,int /*<<< orphan*/ ,int) ; 

void i40iw_next_iw_state(struct i40iw_qp *iwqp,
			 u8 state,
			 u8 del_hash,
			 u8 term,
			 u8 termlen)
{
	struct i40iw_modify_qp_info info;

	memset(&info, 0, sizeof(info));
	info.next_iwarp_state = state;
	info.remove_hash_idx = del_hash;
	info.cq_num_valid = true;
	info.arp_cache_idx_valid = true;
	info.dont_send_term = true;
	info.dont_send_fin = true;
	info.termlen = termlen;

	if (term & I40IWQP_TERM_SEND_TERM_ONLY)
		info.dont_send_term = false;
	if (term & I40IWQP_TERM_SEND_FIN_ONLY)
		info.dont_send_fin = false;
	if (iwqp->sc_qp.term_flags && (state == I40IW_QP_STATE_ERROR))
		info.reset_tcp_conn = true;
	iwqp->hw_iwarp_state = state;
	i40iw_hw_modify_qp(iwqp->iwdev, iwqp, &info, 0);
}