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
typedef  scalar_t__ u16 ;
struct i40iw_virt_mem {int size; struct i40iw_vfdev* va; } ;
struct TYPE_2__ {int /*<<< orphan*/  vchnl_msg; } ;
struct i40iw_vfdev {size_t iw_vf_idx; scalar_t__ pmf_index; TYPE_1__ vf_msg_buffer; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  msg_count; } ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/ ** vf_dev; } ;
struct i40iw_ccq_cqe_info {scalar_t__ op_ret_val; int /*<<< orphan*/  min_err_code; int /*<<< orphan*/  maj_err_code; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_VIRT ; 
 scalar_t__ I40IW_ERR_CQP_COMPL_ERROR ; 
 int /*<<< orphan*/  i40iw_debug (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  i40iw_free_virt_mem (int /*<<< orphan*/ ,struct i40iw_virt_mem*) ; 
 int /*<<< orphan*/  vchnl_pf_send_error_resp (struct i40iw_sc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vchnl_pf_send_get_hmc_fcn_resp (struct i40iw_sc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void pf_cqp_get_hmc_fcn_callback(struct i40iw_sc_dev *dev, void *callback_param,
					struct i40iw_ccq_cqe_info *cqe_info)
{
	struct i40iw_vfdev *vf_dev = callback_param;
	struct i40iw_virt_mem vf_dev_mem;

	if (cqe_info->error) {
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "CQP Completion Error on Get HMC Function.  Maj = 0x%04x, Minor = 0x%04x\n",
			    cqe_info->maj_err_code, cqe_info->min_err_code);
		dev->vf_dev[vf_dev->iw_vf_idx] = NULL;
		vchnl_pf_send_error_resp(dev, vf_dev->vf_id, &vf_dev->vf_msg_buffer.vchnl_msg,
					 (u16)I40IW_ERR_CQP_COMPL_ERROR);
		vf_dev_mem.va = vf_dev;
		vf_dev_mem.size = sizeof(*vf_dev);
		i40iw_free_virt_mem(dev->hw, &vf_dev_mem);
	} else {
		i40iw_debug(dev, I40IW_DEBUG_VIRT,
			    "CQP Completion Operation Return information = 0x%08x\n",
			    cqe_info->op_ret_val);
		vf_dev->pmf_index = (u16)cqe_info->op_ret_val;
		vf_dev->msg_count--;
		vchnl_pf_send_get_hmc_fcn_resp(dev,
					       vf_dev->vf_id,
					       &vf_dev->vf_msg_buffer.vchnl_msg,
					       vf_dev->pmf_index);
	}
}