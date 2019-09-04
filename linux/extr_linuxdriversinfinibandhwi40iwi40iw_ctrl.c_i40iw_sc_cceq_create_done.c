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
struct i40iw_sc_cqp {int dummy; } ;
struct i40iw_sc_ceq {TYPE_1__* dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQP_OP_CREATE_CEQ ; 
 int i40iw_sc_poll_for_cqp_op_done (struct i40iw_sc_cqp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_cceq_create_done(struct i40iw_sc_ceq *ceq)
{
	struct i40iw_sc_cqp *cqp;

	cqp = ceq->dev->cqp;
	return i40iw_sc_poll_for_cqp_op_done(cqp, I40IW_CQP_OP_CREATE_CEQ, NULL);
}