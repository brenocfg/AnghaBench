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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  GLOBAL_PWRMGT_EN ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_smc_dpm_enable (struct radeon_device*,int) ; 

__attribute__((used)) static void kv_start_dpm(struct radeon_device *rdev)
{
	u32 tmp = RREG32_SMC(GENERAL_PWRMGT);

	tmp |= GLOBAL_PWRMGT_EN;
	WREG32_SMC(GENERAL_PWRMGT, tmp);

	kv_smc_dpm_enable(rdev, true);
}