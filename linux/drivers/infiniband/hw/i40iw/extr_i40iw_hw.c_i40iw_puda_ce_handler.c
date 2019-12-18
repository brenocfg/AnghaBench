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
typedef  int u32 ;
struct i40iw_sc_dev {TYPE_1__* ccq_ops; } ;
struct i40iw_sc_cq {int dummy; } ;
struct i40iw_device {int /*<<< orphan*/  sc_dev; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int /*<<< orphan*/  (* ccq_arm ) (struct i40iw_sc_cq*) ;} ;

/* Variables and functions */
 int I40IW_ERR_QUEUE_EMPTY ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int i40iw_puda_poll_completion (struct i40iw_sc_dev*,struct i40iw_sc_cq*,int*) ; 
 int /*<<< orphan*/  stub1 (struct i40iw_sc_cq*) ; 

__attribute__((used)) static void i40iw_puda_ce_handler(struct i40iw_device *iwdev,
				  struct i40iw_sc_cq *cq)
{
	struct i40iw_sc_dev *dev = (struct i40iw_sc_dev *)&iwdev->sc_dev;
	enum i40iw_status_code status;
	u32 compl_error;

	do {
		status = i40iw_puda_poll_completion(dev, cq, &compl_error);
		if (status == I40IW_ERR_QUEUE_EMPTY)
			break;
		if (status) {
			i40iw_pr_err("puda  status = %d\n", status);
			break;
		}
		if (compl_error) {
			i40iw_pr_err("puda compl_err  =0x%x\n", compl_error);
			break;
		}
	} while (1);

	dev->ccq_ops->ccq_arm(cq);
}