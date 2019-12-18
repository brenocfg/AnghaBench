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
typedef  uintptr_t u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct i40iw_sc_cqp {int sq_size; uintptr_t sq_pa; int /*<<< orphan*/  process_cqp_sds; TYPE_1__* dev; int /*<<< orphan*/  sdbuf; scalar_t__ host_ctx_pa; int /*<<< orphan*/  host_ctx; int /*<<< orphan*/  hmc_profile; int /*<<< orphan*/  enabled_vf_count; int /*<<< orphan*/  struct_ver; int /*<<< orphan*/  hw_sq_size; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_CCQPHIGH ; 
 int /*<<< orphan*/  I40E_PFPE_CCQPLOW ; 
 int /*<<< orphan*/  I40E_PFPE_CCQPSTATUS ; 
 int /*<<< orphan*/  I40E_PFPE_CQPERRCODES ; 
 int /*<<< orphan*/  I40E_PFPE_CQPERRCODES_CQP_MAJOR_CODE ; 
 int /*<<< orphan*/  I40E_PFPE_CQPERRCODES_CQP_MINOR_CODE ; 
 int /*<<< orphan*/  I40E_VFPE_CCQPHIGH1 ; 
 int /*<<< orphan*/  I40E_VFPE_CCQPLOW1 ; 
 int /*<<< orphan*/  I40E_VFPE_CCQPSTATUS1 ; 
 int /*<<< orphan*/  I40E_VFPE_CQPERRCODES1 ; 
 int /*<<< orphan*/  I40IW_CQPHC_ENABLED_VFS ; 
 int /*<<< orphan*/  I40IW_CQPHC_HMC_PROFILE ; 
 int /*<<< orphan*/  I40IW_CQPHC_SQSIZE ; 
 int /*<<< orphan*/  I40IW_CQPHC_SVER ; 
 int I40IW_CQP_CTX_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 scalar_t__ I40IW_DONE_COUNT ; 
 int I40IW_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40IW_SD_BUF_ALIGNMENT ; 
 int /*<<< orphan*/  I40IW_SLEEP_COUNT ; 
 int I40IW_UPDATE_SD_BUF_SIZE ; 
 uintptr_t LS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RS_32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RS_32_1 (scalar_t__,int) ; 
 int i40iw_allocate_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ i40iw_rd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_update_sds_noccq ; 
 int /*<<< orphan*/  i40iw_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ ,int,uintptr_t) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_cqp_create(struct i40iw_sc_cqp *cqp,
						  u16 *maj_err,
						  u16 *min_err)
{
	u64 temp;
	u32 cnt = 0, p1, p2, val = 0, err_code;
	enum i40iw_status_code ret_code;

	*maj_err = 0;
	*min_err = 0;

	ret_code = i40iw_allocate_dma_mem(cqp->dev->hw,
					  &cqp->sdbuf,
					  I40IW_UPDATE_SD_BUF_SIZE * cqp->sq_size,
					  I40IW_SD_BUF_ALIGNMENT);

	if (ret_code)
		goto exit;

	temp = LS_64(cqp->hw_sq_size, I40IW_CQPHC_SQSIZE) |
	       LS_64(cqp->struct_ver, I40IW_CQPHC_SVER);

	set_64bit_val(cqp->host_ctx, 0, temp);
	set_64bit_val(cqp->host_ctx, 8, cqp->sq_pa);
	temp = LS_64(cqp->enabled_vf_count, I40IW_CQPHC_ENABLED_VFS) |
	       LS_64(cqp->hmc_profile, I40IW_CQPHC_HMC_PROFILE);
	set_64bit_val(cqp->host_ctx, 16, temp);
	set_64bit_val(cqp->host_ctx, 24, (uintptr_t)cqp);
	set_64bit_val(cqp->host_ctx, 32, 0);
	set_64bit_val(cqp->host_ctx, 40, 0);
	set_64bit_val(cqp->host_ctx, 48, 0);
	set_64bit_val(cqp->host_ctx, 56, 0);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "CQP_HOST_CTX",
			cqp->host_ctx, I40IW_CQP_CTX_SIZE * 8);

	p1 = RS_32_1(cqp->host_ctx_pa, 32);
	p2 = (u32)cqp->host_ctx_pa;

	if (cqp->dev->is_pf) {
		i40iw_wr32(cqp->dev->hw, I40E_PFPE_CCQPHIGH, p1);
		i40iw_wr32(cqp->dev->hw, I40E_PFPE_CCQPLOW, p2);
	} else {
		i40iw_wr32(cqp->dev->hw, I40E_VFPE_CCQPHIGH1, p1);
		i40iw_wr32(cqp->dev->hw, I40E_VFPE_CCQPLOW1, p2);
	}
	do {
		if (cnt++ > I40IW_DONE_COUNT) {
			i40iw_free_dma_mem(cqp->dev->hw, &cqp->sdbuf);
			ret_code = I40IW_ERR_TIMEOUT;
			/*
			 * read PFPE_CQPERRORCODES register to get the minor
			 * and major error code
			 */
			if (cqp->dev->is_pf)
				err_code = i40iw_rd32(cqp->dev->hw, I40E_PFPE_CQPERRCODES);
			else
				err_code = i40iw_rd32(cqp->dev->hw, I40E_VFPE_CQPERRCODES1);
			*min_err = RS_32(err_code, I40E_PFPE_CQPERRCODES_CQP_MINOR_CODE);
			*maj_err = RS_32(err_code, I40E_PFPE_CQPERRCODES_CQP_MAJOR_CODE);
			goto exit;
		}
		udelay(I40IW_SLEEP_COUNT);
		if (cqp->dev->is_pf)
			val = i40iw_rd32(cqp->dev->hw, I40E_PFPE_CCQPSTATUS);
		else
			val = i40iw_rd32(cqp->dev->hw, I40E_VFPE_CCQPSTATUS1);
	} while (!val);

exit:
	if (!ret_code)
		cqp->process_cqp_sds = i40iw_update_sds_noccq;
	return ret_code;
}