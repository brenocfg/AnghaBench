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
struct i40iw_sc_qp {scalar_t__ back_qp; } ;
struct i40iw_qp_flush_info {int dummy; } ;
struct i40iw_qp {int /*<<< orphan*/  rq_drained; int /*<<< orphan*/  sq_drained; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; } ;
struct TYPE_8__ {int min_err_code; int /*<<< orphan*/  maj_err_code; } ;
struct TYPE_5__ {uintptr_t scratch; struct i40iw_sc_qp* qp; struct i40iw_qp_flush_info info; } ;
struct TYPE_6__ {TYPE_1__ qp_flush_wqes; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {TYPE_4__ compl_info; struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
#define  I40IW_CQP_COMPL_RQ_SQ_WQE_FLUSHED 130 
#define  I40IW_CQP_COMPL_RQ_WQE_FLUSHED 129 
#define  I40IW_CQP_COMPL_SQ_WQE_FLUSHED 128 
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  OP_QP_FLUSH_WQES ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  memcpy (struct i40iw_qp_flush_info*,struct i40iw_qp_flush_info*,int) ; 

enum i40iw_status_code i40iw_hw_flush_wqes(struct i40iw_device *iwdev,
					   struct i40iw_sc_qp *qp,
					   struct i40iw_qp_flush_info *info,
					   bool wait)
{
	enum i40iw_status_code status;
	struct i40iw_qp_flush_info *hw_info;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	struct i40iw_qp *iwqp = (struct i40iw_qp *)qp->back_qp;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, wait);
	if (!cqp_request)
		return I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	hw_info = &cqp_request->info.in.u.qp_flush_wqes.info;
	memcpy(hw_info, info, sizeof(*hw_info));

	cqp_info->cqp_cmd = OP_QP_FLUSH_WQES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_flush_wqes.qp = qp;
	cqp_info->in.u.qp_flush_wqes.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status) {
		i40iw_pr_err("CQP-OP Flush WQE's fail");
		complete(&iwqp->sq_drained);
		complete(&iwqp->rq_drained);
		return status;
	}
	if (!cqp_request->compl_info.maj_err_code) {
		switch (cqp_request->compl_info.min_err_code) {
		case I40IW_CQP_COMPL_RQ_WQE_FLUSHED:
			complete(&iwqp->sq_drained);
			break;
		case I40IW_CQP_COMPL_SQ_WQE_FLUSHED:
			complete(&iwqp->rq_drained);
			break;
		case I40IW_CQP_COMPL_RQ_SQ_WQE_FLUSHED:
			break;
		default:
			complete(&iwqp->sq_drained);
			complete(&iwqp->rq_drained);
			break;
		}
	}

	return 0;
}