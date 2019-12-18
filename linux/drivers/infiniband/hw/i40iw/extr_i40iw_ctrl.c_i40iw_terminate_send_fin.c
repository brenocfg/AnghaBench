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
struct i40iw_sc_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQP_TERM_SEND_FIN_ONLY ; 
 int /*<<< orphan*/  I40IW_QP_STATE_TERMINATE ; 
 int /*<<< orphan*/  i40iw_term_modify_qp (struct i40iw_sc_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40iw_terminate_send_fin(struct i40iw_sc_qp *qp)
{
	/* Send the fin only */
	i40iw_term_modify_qp(qp,
			     I40IW_QP_STATE_TERMINATE,
			     I40IWQP_TERM_SEND_FIN_ONLY,
			     0);
}