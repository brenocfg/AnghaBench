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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ras_err_data {int* err_addr; size_t err_addr_cnt; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ADDR_OF_256B_BLOCK (int) ; 
 int ADDR_OF_8KB_BLOCK (int) ; 
 int /*<<< orphan*/  CECC ; 
 int /*<<< orphan*/  ErrorAddr ; 
 int /*<<< orphan*/  LSB ; 
 int /*<<< orphan*/  MCA_UMC_UMC0_MCUMC_ADDRT0 ; 
 int /*<<< orphan*/  MCA_UMC_UMC0_MCUMC_STATUST0 ; 
 int OFFSET_IN_256B_BLOCK (int) ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG64_PCIE (scalar_t__) ; 
 int RREG64_UMC (int) ; 
 int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UECC ; 
 int /*<<< orphan*/  UMC ; 
 int /*<<< orphan*/  Val ; 
 int /*<<< orphan*/  WREG64_UMC (int,int) ; 
 int /*<<< orphan*/  mmMCA_UMC_UMC0_MCUMC_STATUST0 ; 
 scalar_t__ smnMCA_UMC0_MCUMC_ADDRT0 ; 

__attribute__((used)) static void umc_v6_1_query_error_address(struct amdgpu_device *adev,
					 struct ras_err_data *err_data,
					 uint32_t umc_reg_offset, uint32_t channel_index)
{
	uint32_t lsb, mc_umc_status_addr;
	uint64_t mc_umc_status, err_addr;

	mc_umc_status_addr =
		SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);

	/* skip error address process if -ENOMEM */
	if (!err_data->err_addr) {
		/* clear umc status */
		WREG64_UMC(mc_umc_status_addr + umc_reg_offset, 0x0ULL);
		return;
	}

	mc_umc_status = RREG64_UMC(mc_umc_status_addr + umc_reg_offset);

	/* calculate error address if ue/ce error is detected */
	if (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1 &&
	    (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)) {
		err_addr = RREG64_PCIE(smnMCA_UMC0_MCUMC_ADDRT0 + umc_reg_offset * 4);

		/* the lowest lsb bits should be ignored */
		lsb = REG_GET_FIELD(err_addr, MCA_UMC_UMC0_MCUMC_ADDRT0, LSB);
		err_addr = REG_GET_FIELD(err_addr, MCA_UMC_UMC0_MCUMC_ADDRT0, ErrorAddr);
		err_addr &= ~((0x1ULL << lsb) - 1);

		/* translate umc channel address to soc pa, 3 parts are included */
		err_data->err_addr[err_data->err_addr_cnt] =
						ADDR_OF_8KB_BLOCK(err_addr) |
						ADDR_OF_256B_BLOCK(channel_index) |
						OFFSET_IN_256B_BLOCK(err_addr);

		err_data->err_addr_cnt++;
	}

	/* clear umc status */
	WREG64_UMC(mc_umc_status_addr + umc_reg_offset, 0x0ULL);
}