#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct i40iw_sc_dev {TYPE_2__* ccq_ops; } ;
struct i40iw_sc_cq {int dummy; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; struct i40iw_sc_dev sc_dev; } ;
struct TYPE_3__ {scalar_t__ error; int /*<<< orphan*/  op_ret_val; int /*<<< orphan*/  min_err_code; int /*<<< orphan*/  maj_err_code; } ;
struct i40iw_cqp_request {int request_done; int /*<<< orphan*/  (* callback_fcn ) (struct i40iw_cqp_request*,int) ;int /*<<< orphan*/  waitq; scalar_t__ waiting; TYPE_1__ compl_info; } ;
struct i40iw_ccq_cqe_info {scalar_t__ error; int /*<<< orphan*/  op_ret_val; int /*<<< orphan*/  min_err_code; int /*<<< orphan*/  maj_err_code; int /*<<< orphan*/  op_code; scalar_t__ scratch; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {int (* ccq_get_cqe_info ) (struct i40iw_sc_cq*,struct i40iw_ccq_cqe_info*) ;int /*<<< orphan*/  (* ccq_arm ) (struct i40iw_sc_cq*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_process_bh (struct i40iw_sc_dev*) ; 
 int /*<<< orphan*/  i40iw_put_cqp_request (int /*<<< orphan*/ *,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  memset (struct i40iw_ccq_cqe_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct i40iw_sc_cq*,struct i40iw_ccq_cqe_info*) ; 
 int /*<<< orphan*/  stub2 (struct i40iw_cqp_request*,int) ; 
 int /*<<< orphan*/  stub3 (struct i40iw_sc_cq*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_cqp_ce_handler(struct i40iw_device *iwdev, struct i40iw_sc_cq *cq, bool arm)
{
	struct i40iw_cqp_request *cqp_request;
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	u32 cqe_count = 0;
	struct i40iw_ccq_cqe_info info;
	int ret;

	do {
		memset(&info, 0, sizeof(info));
		ret = dev->ccq_ops->ccq_get_cqe_info(cq, &info);
		if (ret)
			break;
		cqp_request = (struct i40iw_cqp_request *)(unsigned long)info.scratch;
		if (info.error)
			i40iw_pr_err("opcode = 0x%x maj_err_code = 0x%x min_err_code = 0x%x\n",
				     info.op_code, info.maj_err_code, info.min_err_code);
		if (cqp_request) {
			cqp_request->compl_info.maj_err_code = info.maj_err_code;
			cqp_request->compl_info.min_err_code = info.min_err_code;
			cqp_request->compl_info.op_ret_val = info.op_ret_val;
			cqp_request->compl_info.error = info.error;

			if (cqp_request->waiting) {
				cqp_request->request_done = true;
				wake_up(&cqp_request->waitq);
				i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
			} else {
				if (cqp_request->callback_fcn)
					cqp_request->callback_fcn(cqp_request, 1);
				i40iw_put_cqp_request(&iwdev->cqp, cqp_request);
			}
		}

		cqe_count++;
	} while (1);

	if (arm && cqe_count) {
		i40iw_process_bh(dev);
		dev->ccq_ops->ccq_arm(cq);
	}
}