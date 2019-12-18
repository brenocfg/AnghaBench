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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_virtchnl_op_buf {scalar_t__ iw_chnl_buf; } ;
struct i40iw_virtchnl_hmc_obj_range {size_t obj_type; int /*<<< orphan*/  obj_count; int /*<<< orphan*/  start_index; } ;
struct i40iw_hmc_info {TYPE_2__* hmc_obj; } ;
struct TYPE_3__ {struct i40iw_virtchnl_op_buf vchnl_msg; } ;
struct i40iw_vfdev {int pf_hmc_initialized; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  pf_dev; int /*<<< orphan*/  msg_count; struct i40iw_hmc_info hmc_info; scalar_t__ pmf_index; TYPE_1__ vf_msg_buffer; } ;
struct i40iw_hmc_create_obj_info {int is_pf; scalar_t__ rsrc_type; int /*<<< orphan*/  count; int /*<<< orphan*/  start_idx; int /*<<< orphan*/  entry_type; struct i40iw_hmc_info* hmc_info; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_4__ {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_VIRT ; 
 scalar_t__ I40IW_HMC_IW_PBLE ; 
 int /*<<< orphan*/  I40IW_SD_TYPE_DIRECT ; 
 int /*<<< orphan*/  I40IW_SD_TYPE_PAGED ; 
 int /*<<< orphan*/  i40iw_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int i40iw_pf_init_vfhmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i40iw_sc_create_hmc_obj (int /*<<< orphan*/ ,struct i40iw_hmc_create_obj_info*) ; 
 int /*<<< orphan*/  memset (struct i40iw_hmc_create_obj_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vchnl_pf_send_error_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40iw_virtchnl_op_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pf_add_hmc_obj_callback(void *work_vf_dev)
{
	struct i40iw_vfdev *vf_dev = (struct i40iw_vfdev *)work_vf_dev;
	struct i40iw_hmc_info *hmc_info = &vf_dev->hmc_info;
	struct i40iw_virtchnl_op_buf *vchnl_msg = &vf_dev->vf_msg_buffer.vchnl_msg;
	struct i40iw_hmc_create_obj_info info;
	struct i40iw_virtchnl_hmc_obj_range *add_hmc_obj;
	enum i40iw_status_code ret_code;

	if (!vf_dev->pf_hmc_initialized) {
		ret_code = i40iw_pf_init_vfhmc(vf_dev->pf_dev, (u8)vf_dev->pmf_index, NULL);
		if (ret_code)
			goto add_out;
		vf_dev->pf_hmc_initialized = true;
	}

	add_hmc_obj = (struct i40iw_virtchnl_hmc_obj_range *)vchnl_msg->iw_chnl_buf;

	memset(&info, 0, sizeof(info));
	info.hmc_info = hmc_info;
	info.is_pf = false;
	info.rsrc_type = (u32)add_hmc_obj->obj_type;
	info.entry_type = (info.rsrc_type == I40IW_HMC_IW_PBLE) ? I40IW_SD_TYPE_PAGED : I40IW_SD_TYPE_DIRECT;
	info.start_idx = add_hmc_obj->start_index;
	info.count = add_hmc_obj->obj_count;
	i40iw_debug(vf_dev->pf_dev, I40IW_DEBUG_VIRT,
		    "I40IW_VCHNL_OP_ADD_HMC_OBJ_RANGE.  Add %u type %u objects\n",
		    info.count, info.rsrc_type);
	ret_code = i40iw_sc_create_hmc_obj(vf_dev->pf_dev, &info);
	if (!ret_code)
		vf_dev->hmc_info.hmc_obj[add_hmc_obj->obj_type].cnt = add_hmc_obj->obj_count;
add_out:
	vf_dev->msg_count--;
	vchnl_pf_send_error_resp(vf_dev->pf_dev, vf_dev->vf_id, vchnl_msg, (u16)ret_code);
}