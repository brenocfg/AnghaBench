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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_virtchnl_op_buf {scalar_t__ iw_chnl_buf; } ;
struct i40iw_virtchnl_hmc_obj_range {int /*<<< orphan*/  obj_count; int /*<<< orphan*/  start_index; scalar_t__ obj_type; } ;
struct TYPE_2__ {struct i40iw_virtchnl_op_buf vchnl_msg; } ;
struct i40iw_hmc_info {int dummy; } ;
struct i40iw_vfdev {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  pf_dev; int /*<<< orphan*/  msg_count; int /*<<< orphan*/  pf_hmc_initialized; TYPE_1__ vf_msg_buffer; struct i40iw_hmc_info hmc_info; } ;
struct i40iw_hmc_del_obj_info {int is_pf; scalar_t__ rsrc_type; int /*<<< orphan*/  count; int /*<<< orphan*/  start_idx; struct i40iw_hmc_info* hmc_info; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_VIRT ; 
 int I40IW_SUCCESS ; 
 int /*<<< orphan*/  i40iw_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int i40iw_sc_del_hmc_obj (int /*<<< orphan*/ ,struct i40iw_hmc_del_obj_info*,int) ; 
 int /*<<< orphan*/  memset (struct i40iw_hmc_del_obj_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vchnl_pf_send_error_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40iw_virtchnl_op_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pf_del_hmc_obj_callback(void *work_vf_dev)
{
	struct i40iw_vfdev *vf_dev = (struct i40iw_vfdev *)work_vf_dev;
	struct i40iw_hmc_info *hmc_info = &vf_dev->hmc_info;
	struct i40iw_virtchnl_op_buf *vchnl_msg = &vf_dev->vf_msg_buffer.vchnl_msg;
	struct i40iw_hmc_del_obj_info info;
	struct i40iw_virtchnl_hmc_obj_range *del_hmc_obj;
	enum i40iw_status_code ret_code = I40IW_SUCCESS;

	if (!vf_dev->pf_hmc_initialized)
		goto del_out;

	del_hmc_obj = (struct i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;

	memset(&info, 0, sizeof(info));
	info.hmc_info = hmc_info;
	info.is_pf = false;
	info.rsrc_type = (u32)del_hmc_obj->obj_type;
	info.start_idx = del_hmc_obj->start_index;
	info.count = del_hmc_obj->obj_count;
	i40iw_debug(vf_dev->pf_dev, I40IW_DEBUG_VIRT,
		    "I40IW_VCHNL_OP_DEL_HMC_OBJ_RANGE.  Delete %u type %u objects\n",
		    info.count, info.rsrc_type);
	ret_code = i40iw_sc_del_hmc_obj(vf_dev->pf_dev, &info, false);
del_out:
	vf_dev->msg_count--;
	vchnl_pf_send_error_resp(vf_dev->pf_dev, vf_dev->vf_id, vchnl_msg, (u16)ret_code);
}