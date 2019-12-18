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
struct i40iw_sc_cq {int dummy; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; } ;
struct TYPE_4__ {uintptr_t scratch; struct i40iw_sc_cq* cq; } ;
struct TYPE_5__ {TYPE_1__ cq_destroy; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CQ_DESTROY ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 

void i40iw_cq_wq_destroy(struct i40iw_device *iwdev, struct i40iw_sc_cq *cq)
{
	enum i40iw_status_code status;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request)
		return;

	cqp_info = &cqp_request->info;

	cqp_info->cqp_cmd = OP_CQ_DESTROY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_destroy.cq = cq;
	cqp_info->in.u.cq_destroy.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP-OP Destroy QP fail");
}