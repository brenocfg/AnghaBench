#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ras_err_data {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EccErrCntCsSel ; 
 int /*<<< orphan*/  EccErrInt ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMC ; 
 int /*<<< orphan*/  UMCCH0_0_EccErrCntSel ; 
 scalar_t__ UMC_V6_1_CE_CNT_INIT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmUMCCH0_0_EccErrCnt ; 
 int /*<<< orphan*/  mmUMCCH0_0_EccErrCntSel ; 

__attribute__((used)) static void umc_v6_1_ras_init_per_channel(struct amdgpu_device *adev,
					 struct ras_err_data *err_data,
					 uint32_t umc_reg_offset, uint32_t channel_index)
{
	uint32_t ecc_err_cnt_sel, ecc_err_cnt_sel_addr;
	uint32_t ecc_err_cnt_addr;

	ecc_err_cnt_sel_addr =
		SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel);
	ecc_err_cnt_addr =
		SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt);

	/* select the lower chip and check the error count */
	ecc_err_cnt_sel = RREG32(ecc_err_cnt_sel_addr + umc_reg_offset);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 0);
	/* set ce error interrupt type to APIC based interrupt */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrInt, 0x1);
	WREG32(ecc_err_cnt_sel_addr + umc_reg_offset, ecc_err_cnt_sel);
	/* set error count to initial value */
	WREG32(ecc_err_cnt_addr + umc_reg_offset, UMC_V6_1_CE_CNT_INIT);

	/* select the higher chip and check the err counter */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 1);
	WREG32(ecc_err_cnt_sel_addr + umc_reg_offset, ecc_err_cnt_sel);
	WREG32(ecc_err_cnt_addr + umc_reg_offset, UMC_V6_1_CE_CNT_INIT);
}