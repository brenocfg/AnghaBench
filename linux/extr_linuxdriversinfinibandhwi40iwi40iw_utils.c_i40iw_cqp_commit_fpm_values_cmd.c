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
typedef  int /*<<< orphan*/  u8 ;
struct i40iw_sc_dev {int /*<<< orphan*/  cqp; scalar_t__ back_dev; } ;
struct i40iw_dma_mem {int /*<<< orphan*/  va; int /*<<< orphan*/  pa; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; } ;
struct TYPE_4__ {uintptr_t scratch; int /*<<< orphan*/  hmc_fn_id; int /*<<< orphan*/  fpm_values_va; int /*<<< orphan*/  fpm_values_pa; int /*<<< orphan*/  cqp; } ;
struct TYPE_5__ {TYPE_1__ commit_fpm_values; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {int /*<<< orphan*/ * param; struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  OP_COMMIT_FPM_VALUES ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 

enum i40iw_status_code i40iw_cqp_commit_fpm_values_cmd(struct i40iw_sc_dev *dev,
						       struct i40iw_dma_mem *values_mem,
						       u8 hmc_fn_id)
{
	enum i40iw_status_code status;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, true);
	if (!cqp_request)
		return I40IW_ERR_NO_MEMORY;
	cqp_info = &cqp_request->info;
	cqp_request->param = NULL;
	cqp_info->in.u.commit_fpm_values.cqp = dev->cqp;
	cqp_info->in.u.commit_fpm_values.fpm_values_pa = values_mem->pa;
	cqp_info->in.u.commit_fpm_values.fpm_values_va = values_mem->va;
	cqp_info->in.u.commit_fpm_values.hmc_fn_id = hmc_fn_id;
	cqp_info->cqp_cmd = OP_COMMIT_FPM_VALUES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.commit_fpm_values.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP-OP Commit FPM fail");
	return status;
}