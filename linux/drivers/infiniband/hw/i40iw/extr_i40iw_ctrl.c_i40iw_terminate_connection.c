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
struct i40iw_sc_qp {int term_flags; int /*<<< orphan*/  eventtype; } ;
struct i40iw_aeqe_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQP_TERM_SEND_TERM_ONLY ; 
 int /*<<< orphan*/  I40IW_QP_STATE_TERMINATE ; 
 int I40IW_TERM_SENT ; 
 int /*<<< orphan*/  TERM_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  i40iw_bld_terminate_hdr (struct i40iw_sc_qp*,struct i40iw_aeqe_info*) ; 
 int /*<<< orphan*/  i40iw_term_modify_qp (struct i40iw_sc_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_terminate_start_timer (struct i40iw_sc_qp*) ; 

void i40iw_terminate_connection(struct i40iw_sc_qp *qp, struct i40iw_aeqe_info *info)
{
	u8 termlen = 0;

	if (qp->term_flags & I40IW_TERM_SENT)
		return;         /* Sanity check */

	/* Eventtype can change from bld_terminate_hdr */
	qp->eventtype = TERM_EVENT_QP_FATAL;
	termlen = i40iw_bld_terminate_hdr(qp, info);
	i40iw_terminate_start_timer(qp);
	qp->term_flags |= I40IW_TERM_SENT;
	i40iw_term_modify_qp(qp, I40IW_QP_STATE_TERMINATE,
			     I40IWQP_TERM_SEND_TERM_ONLY, termlen);
}