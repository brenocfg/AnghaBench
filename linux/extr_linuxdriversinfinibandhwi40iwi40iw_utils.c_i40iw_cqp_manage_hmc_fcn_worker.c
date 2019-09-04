#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct virtchnl_work {struct i40iw_cqp_request* cqp_request; } ;
struct i40iw_hmc_fcn_info {int /*<<< orphan*/  cqp_callback_param; int /*<<< orphan*/  (* callback_fcn ) (TYPE_6__*,int /*<<< orphan*/ ,struct i40iw_ccq_cqe_info*) ;} ;
struct i40iw_device {int /*<<< orphan*/  cqp; } ;
struct TYPE_8__ {TYPE_6__* dev; struct i40iw_hmc_fcn_info info; } ;
struct TYPE_9__ {TYPE_2__ manage_hmc_pm; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct TYPE_11__ {TYPE_4__ in; } ;
struct TYPE_7__ {int /*<<< orphan*/  error; int /*<<< orphan*/  op_ret_val; int /*<<< orphan*/  op_code; int /*<<< orphan*/  min_err_code; int /*<<< orphan*/  maj_err_code; } ;
struct i40iw_cqp_request {TYPE_5__ info; TYPE_1__ compl_info; } ;
struct i40iw_ccq_cqe_info {int /*<<< orphan*/  error; scalar_t__ scratch; int /*<<< orphan*/  op_ret_val; int /*<<< orphan*/  op_code; int /*<<< orphan*/  min_err_code; int /*<<< orphan*/  maj_err_code; int /*<<< orphan*/ * cqp; } ;
struct TYPE_12__ {scalar_t__ back_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_put_cqp_request (int /*<<< orphan*/ *,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,struct i40iw_ccq_cqe_info*) ; 

__attribute__((used)) static void i40iw_cqp_manage_hmc_fcn_worker(struct work_struct *work)
{
	struct i40iw_cqp_request *cqp_request =
	    ((struct virtchnl_work *)work)->cqp_request;
	struct i40iw_ccq_cqe_info ccq_cqe_info;
	struct i40iw_hmc_fcn_info *hmcfcninfo =
			&cqp_request->info.in.u.manage_hmc_pm.info;
	struct i40iw_device *iwdev =
	    (struct i40iw_device *)cqp_request->info.in.u.manage_hmc_pm.dev->back_dev;

	ccq_cqe_info.cqp = NULL;
	ccq_cqe_info.maj_err_code = cqp_request->compl_info.maj_err_code;
	ccq_cqe_info.min_err_code = cqp_request->compl_info.min_err_code;
	ccq_cqe_info.op_code = cqp_request->compl_info.op_code;
	ccq_cqe_info.op_ret_val = cqp_request->compl_info.op_ret_val;
	ccq_cqe_info.scratch = 0;
	ccq_cqe_info.error = cqp_request->compl_info.error;
	hmcfcninfo->callback_fcn(cqp_request->info.in.u.manage_hmc_pm.dev,
				 hmcfcninfo->cqp_callback_param, &ccq_cqe_info);
	i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
}