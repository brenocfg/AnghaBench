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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct i40iw_sc_dev {scalar_t__ hmc_fn_id; int /*<<< orphan*/ * fpm_commit_buf; int /*<<< orphan*/  cqp; int /*<<< orphan*/  fpm_commit_buf_pa; struct i40iw_hmc_info* hmc_info; } ;
struct i40iw_hmc_obj_info {scalar_t__ cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd_cnt; } ;
struct i40iw_hmc_info {TYPE_1__ sd_table; struct i40iw_hmc_obj_info* hmc_obj; int /*<<< orphan*/  hmc_fn_id; } ;
struct i40iw_dma_mem {int /*<<< orphan*/ * va; int /*<<< orphan*/  pa; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_COMMIT_FPM_BUF_SIZE ; 
 scalar_t__ I40IW_CQP_WAIT_POLL_CQ ; 
 scalar_t__ I40IW_CQP_WAIT_POLL_REGS ; 
 int /*<<< orphan*/  I40IW_DEBUG_HMC ; 
 int I40IW_ERR_BAD_PTR ; 
 int I40IW_ERR_INVALID_HMCFN_ID ; 
 scalar_t__ I40IW_FIRST_VF_FPM_ID ; 
 size_t I40IW_HMC_IW_PBLE ; 
 size_t I40IW_HMC_IW_QP ; 
 scalar_t__ I40IW_MAX_VF_FPM_ID ; 
 int /*<<< orphan*/  i40iw_debug_buf (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40iw_sc_commit_fpm_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i40iw_dma_mem*,int,scalar_t__) ; 
 int i40iw_sc_parse_fpm_commit_buf (int /*<<< orphan*/ *,struct i40iw_hmc_obj_info*,int /*<<< orphan*/ *) ; 
 struct i40iw_hmc_info* i40iw_vf_hmcinfo_from_fpm (struct i40iw_sc_dev*,scalar_t__) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_configure_iw_fpm(struct i40iw_sc_dev *dev,
							u8 hmc_fn_id)
{
	struct i40iw_hmc_info *hmc_info;
	struct i40iw_hmc_obj_info *obj_info;
	u64 *buf;
	struct i40iw_dma_mem commit_fpm_mem;
	u32 i, j;
	enum i40iw_status_code ret_code = 0;
	bool poll_registers = true;
	u8 wait_type;

	if (hmc_fn_id >= I40IW_MAX_VF_FPM_ID ||
	    (dev->hmc_fn_id != hmc_fn_id && hmc_fn_id < I40IW_FIRST_VF_FPM_ID))
		return I40IW_ERR_INVALID_HMCFN_ID;

	if (hmc_fn_id == dev->hmc_fn_id) {
		hmc_info = dev->hmc_info;
	} else {
		hmc_info = i40iw_vf_hmcinfo_from_fpm(dev, hmc_fn_id);
		poll_registers = false;
	}
	if (!hmc_info)
		return I40IW_ERR_BAD_PTR;

	obj_info = hmc_info->hmc_obj;
	buf = dev->fpm_commit_buf;

	/* copy cnt values in commit buf */
	for (i = I40IW_HMC_IW_QP, j = 0; i <= I40IW_HMC_IW_PBLE;
	     i++, j += 8)
		set_64bit_val(buf, j, (u64)obj_info[i].cnt);

	set_64bit_val(buf, 40, 0);   /* APBVT rsvd */

	commit_fpm_mem.pa = dev->fpm_commit_buf_pa;
	commit_fpm_mem.va = dev->fpm_commit_buf;
	wait_type = poll_registers ? (u8)I40IW_CQP_WAIT_POLL_REGS :
			(u8)I40IW_CQP_WAIT_POLL_CQ;
	ret_code = i40iw_sc_commit_fpm_values(
					dev->cqp,
					0,
					hmc_info->hmc_fn_id,
					&commit_fpm_mem,
					true,
					wait_type);

	/* parse the fpm_commit_buf and fill hmc obj info */
	if (!ret_code)
		ret_code = i40iw_sc_parse_fpm_commit_buf(dev->fpm_commit_buf,
							 hmc_info->hmc_obj,
							 &hmc_info->sd_table.sd_cnt);

	i40iw_debug_buf(dev, I40IW_DEBUG_HMC, "COMMIT FPM BUFFER",
			commit_fpm_mem.va, I40IW_COMMIT_FPM_BUF_SIZE);

	return ret_code;
}