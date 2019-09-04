#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ib_qp {int dummy; } ;
struct TYPE_5__ {size_t qp_num; } ;
struct i40iw_qp {int /*<<< orphan*/  iwpd; int /*<<< orphan*/  sc_qp; TYPE_1__ ibqp; int /*<<< orphan*/  refcount; struct i40iw_device* iwdev; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; int /*<<< orphan*/  qptable_lock; int /*<<< orphan*/ ** qp_table; } ;
struct TYPE_6__ {uintptr_t scratch; int remove_hash_idx; int /*<<< orphan*/ * qp; } ;
struct TYPE_7__ {TYPE_2__ qp_destroy; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_4__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; void* param; int /*<<< orphan*/  callback_fcn; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  OP_QP_DESTROY ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_qp ; 
 int /*<<< orphan*/  i40iw_free_qp_resources (struct i40iw_device*,struct i40iw_qp*,size_t) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_rem_devusecount (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_rem_pdusecount (int /*<<< orphan*/ ,struct i40iw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i40iw_qp* to_iwqp (struct ib_qp*) ; 

void i40iw_rem_ref(struct ib_qp *ibqp)
{
	struct i40iw_qp *iwqp;
	enum i40iw_status_code status;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	struct i40iw_device *iwdev;
	u32 qp_num;
	unsigned long flags;

	iwqp = to_iwqp(ibqp);
	iwdev = iwqp->iwdev;
	spin_lock_irqsave(&iwdev->qptable_lock, flags);
	if (!atomic_dec_and_test(&iwqp->refcount)) {
		spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
		return;
	}

	qp_num = iwqp->ibqp.qp_num;
	iwdev->qp_table[qp_num] = NULL;
	spin_unlock_irqrestore(&iwdev->qptable_lock, flags);
	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, false);
	if (!cqp_request)
		return;

	cqp_request->callback_fcn = i40iw_free_qp;
	cqp_request->param = (void *)&iwqp->sc_qp;
	cqp_info = &cqp_request->info;
	cqp_info->cqp_cmd = OP_QP_DESTROY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_destroy.qp = &iwqp->sc_qp;
	cqp_info->in.u.qp_destroy.scratch = (uintptr_t)cqp_request;
	cqp_info->in.u.qp_destroy.remove_hash_idx = true;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (!status)
		return;

	i40iw_rem_pdusecount(iwqp->iwpd, iwdev);
	i40iw_free_qp_resources(iwdev, iwqp, qp_num);
	i40iw_rem_devusecount(iwdev);
}