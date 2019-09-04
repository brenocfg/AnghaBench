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
struct radeon_device {int usec_timeout; } ;
struct ci_power_info {int /*<<< orphan*/  sram_end; } ;

/* Variables and functions */
 int BOOT_SEQ_DONE ; 
 int /*<<< orphan*/  RCU_UC_EVENTS ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_SYSCON_MISC_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_load_smc_ucode (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_reset_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_stop_smc_clock (struct radeon_device*) ; 

__attribute__((used)) static int ci_upload_firmware(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	int i, ret;

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32_SMC(RCU_UC_EVENTS) & BOOT_SEQ_DONE)
			break;
	}
	WREG32_SMC(SMC_SYSCON_MISC_CNTL, 1);

	ci_stop_smc_clock(rdev);
	ci_reset_smc(rdev);

	ret = ci_load_smc_ucode(rdev, pi->sram_end);

	return ret;

}