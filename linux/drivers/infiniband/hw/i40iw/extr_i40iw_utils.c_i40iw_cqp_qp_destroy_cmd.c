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
struct i40iw_sc_qp {int dummy; } ;
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_cqp {int dummy; } ;
struct i40iw_device {struct i40iw_cqp cqp; } ;
struct TYPE_4__ {uintptr_t scratch; int remove_hash_idx; struct i40iw_sc_qp* qp; } ;
struct TYPE_5__ {TYPE_1__ qp_destroy; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  OP_QP_DESTROY ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (struct i40iw_cqp*,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  memset (struct cqp_commands_info*,int /*<<< orphan*/ ,int) ; 

void i40iw_cqp_qp_destroy_cmd(struct i40iw_sc_dev *dev, struct i40iw_sc_qp *qp)
{
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;
	struct i40iw_cqp *iwcqp = &iwdev->cqp;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	enum i40iw_status_code status;

	cqp_request = i40iw_get_cqp_request(iwcqp, true);
	if (!cqp_request)
		return;

	cqp_info = &cqp_request->info;
	memset(cqp_info, 0, sizeof(*cqp_info));

	cqp_info->cqp_cmd = OP_QP_DESTROY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_destroy.qp = qp;
	cqp_info->in.u.qp_destroy.scratch = (uintptr_t)cqp_request;
	cqp_info->in.u.qp_destroy.remove_hash_idx = true;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP QP_DESTROY fail");
}