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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Deferred ; 
 int /*<<< orphan*/  MCA_UMC_UMC0_MCUMC_STATUST0 ; 
 int /*<<< orphan*/  PCC ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG64_UMC (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCC ; 
 int /*<<< orphan*/  UC ; 
 int /*<<< orphan*/  UECC ; 
 int /*<<< orphan*/  UMC ; 
 int /*<<< orphan*/  Val ; 
 int /*<<< orphan*/  mmMCA_UMC_UMC0_MCUMC_STATUST0 ; 

__attribute__((used)) static void umc_v6_1_querry_uncorrectable_error_count(struct amdgpu_device *adev,
						      uint32_t umc_reg_offset,
						      unsigned long *error_count)
{
	uint64_t mc_umc_status;
	uint32_t mc_umc_status_addr;

	mc_umc_status_addr =
                SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);

	/* check the MCUMC_STATUS */
	mc_umc_status = RREG64_UMC(mc_umc_status_addr + umc_reg_offset);
	if ((REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1) &&
	    (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Deferred) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1))
		*error_count += 1;
}