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
struct i40iw_manage_vf_pble_info {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sc_cqp; } ;
struct i40iw_device {scalar_t__ init_state; TYPE_4__ cqp; } ;
struct TYPE_5__ {uintptr_t scratch; int /*<<< orphan*/ * cqp; struct i40iw_manage_vf_pble_info info; } ;
struct TYPE_6__ {TYPE_1__ manage_vf_pble_bp; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 scalar_t__ CCQ_CREATED ; 
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  OP_MANAGE_VF_PBLE_BP ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (TYPE_4__*,int) ; 
 int i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  memcpy (struct i40iw_manage_vf_pble_info*,struct i40iw_manage_vf_pble_info*,int) ; 

enum i40iw_status_code i40iw_hw_manage_vf_pble_bp(struct i40iw_device *iwdev,
						  struct i40iw_manage_vf_pble_info *info,
						  bool wait)
{
	enum i40iw_status_code status;
	struct i40iw_manage_vf_pble_info *hw_info;
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;

	if ((iwdev->init_state < CCQ_CREATED) && wait)
		wait = false;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, wait);
	if (!cqp_request)
		return I40IW_ERR_NO_MEMORY;

	cqp_info = &cqp_request->info;
	hw_info = &cqp_request->info.in.u.manage_vf_pble_bp.info;
	memcpy(hw_info, info, sizeof(*hw_info));

	cqp_info->cqp_cmd = OP_MANAGE_VF_PBLE_BP;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_vf_pble_bp.cqp = &iwdev->cqp.sc_cqp;
	cqp_info->in.u.manage_vf_pble_bp.scratch = (uintptr_t)cqp_request;
	status = i40iw_handle_cqp_op(iwdev, cqp_request);
	if (status)
		i40iw_pr_err("CQP-OP Manage VF pble_bp fail");
	return status;
}