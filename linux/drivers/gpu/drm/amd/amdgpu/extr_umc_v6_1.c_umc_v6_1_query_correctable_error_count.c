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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CECC ; 
 int /*<<< orphan*/  EccErrCnt ; 
 int /*<<< orphan*/  EccErrCntCsSel ; 
 int /*<<< orphan*/  ErrorCodeExt ; 
 int /*<<< orphan*/  MCA_UMC_UMC0_MCUMC_STATUST0 ; 
 int REG_GET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 scalar_t__ RREG64_UMC (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMC ; 
 int /*<<< orphan*/  UMCCH0_0_EccErrCnt ; 
 int /*<<< orphan*/  UMCCH0_0_EccErrCntSel ; 
 scalar_t__ UMC_V6_1_CE_CNT_INIT ; 
 int /*<<< orphan*/  Val ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmMCA_UMC_UMC0_MCUMC_STATUST0 ; 
 int /*<<< orphan*/  mmUMCCH0_0_EccErrCnt ; 
 int /*<<< orphan*/  mmUMCCH0_0_EccErrCntSel ; 

__attribute__((used)) static void umc_v6_1_query_correctable_error_count(struct amdgpu_device *adev,
						   uint32_t umc_reg_offset,
						   unsigned long *error_count)
{
	uint32_t ecc_err_cnt_sel, ecc_err_cnt_sel_addr;
	uint32_t ecc_err_cnt, ecc_err_cnt_addr;
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addr;

	ecc_err_cnt_sel_addr =
		SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel);
	ecc_err_cnt_addr =
		SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt);
	mc_umc_status_addr =
		SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);

	/* select the lower chip and check the error count */
	ecc_err_cnt_sel = RREG32(ecc_err_cnt_sel_addr + umc_reg_offset);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 0);
	WREG32(ecc_err_cnt_sel_addr + umc_reg_offset, ecc_err_cnt_sel);
	ecc_err_cnt = RREG32(ecc_err_cnt_addr + umc_reg_offset);
	*error_count +=
		(REG_GET_FIELD(ecc_err_cnt, UMCCH0_0_EccErrCnt, EccErrCnt) -
		 UMC_V6_1_CE_CNT_INIT);
	/* clear the lower chip err count */
	WREG32(ecc_err_cnt_addr + umc_reg_offset, UMC_V6_1_CE_CNT_INIT);

	/* select the higher chip and check the err counter */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 1);
	WREG32(ecc_err_cnt_sel_addr + umc_reg_offset, ecc_err_cnt_sel);
	ecc_err_cnt = RREG32(ecc_err_cnt_addr + umc_reg_offset);
	*error_count +=
		(REG_GET_FIELD(ecc_err_cnt, UMCCH0_0_EccErrCnt, EccErrCnt) -
		 UMC_V6_1_CE_CNT_INIT);
	/* clear the higher chip err count */
	WREG32(ecc_err_cnt_addr + umc_reg_offset, UMC_V6_1_CE_CNT_INIT);

	/* check for SRAM correctable error
	  MCUMC_STATUS is a 64 bit register */
	mc_umc_status = RREG64_UMC(mc_umc_status_addr + umc_reg_offset);
	if (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, ErrorCodeExt) == 6 &&
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1 &&
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)
		*error_count += 1;
}