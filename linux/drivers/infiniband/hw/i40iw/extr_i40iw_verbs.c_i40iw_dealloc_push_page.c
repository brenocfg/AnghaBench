#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i40iw_sc_qp {scalar_t__ push_idx; int /*<<< orphan*/  qs_handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  sc_cqp; } ;
struct i40iw_device {TYPE_5__ cqp; } ;
struct TYPE_6__ {scalar_t__ push_idx; int free_page; int /*<<< orphan*/  qs_handle; } ;
struct TYPE_7__ {uintptr_t scratch; int /*<<< orphan*/ * cqp; TYPE_1__ info; } ;
struct TYPE_8__ {TYPE_2__ manage_push_page; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_4__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 scalar_t__ I40IW_INVALID_PUSH_PAGE_INDEX ; 
 int /*<<< orphan*/  OP_MANAGE_PUSH_PAGE ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (TYPE_5__*,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 

__attribute__((used)) static void i40iw_dealloc_push_page(struct i40iw_device *iwdev, struct i40iw_sc_qp *qp)
{
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	enum i40iw_status_code status;

	if (qp->push_idx == I40IW_INVALID_PUSH_PAGE_INDEX)
		return;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, false);
	if (!cqp_request)
		return;

	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_MANAGE_PUSH_PAGE;
	cqp_info->post_sq = 1;

	cqp_info->in.u.manage_push_page.info.push_idx = qp->push_idx;
	cqp_info->in.u.manage_push_page.info.qs_handle = qp->qs_handle;
	cqp_info->in.u.manage_push_page.info.free_page = 1;
	cqp_info->in.u.manage_push_page.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.manage_push_page.scratch = (uintptr_t)cqp_request;

	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (!status)
		qp->push_idx = I40IW_INVALID_PUSH_PAGE_INDEX;
	else
		i40iw_pr_err("CQP-OP Push page fail");
}