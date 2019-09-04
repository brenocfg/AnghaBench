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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_I_CNTL_1 ; 
 int /*<<< orphan*/  PM_TP ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_DPM (int) ; 
 int SCLK_DPM_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int,int,int,int*,int*) ; 
 int radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static void trinity_program_sclk_dpm(struct radeon_device *rdev)
{
	u32 p, u;
	u32 tp = RREG32_SMC(PM_TP);
	u32 ni;
	u32 xclk = radeon_get_xclk(rdev);
	u32 value;

	r600_calculate_u_and_p(400, xclk, 16, &p, &u);

	ni = (p + tp - 1) / tp;

	value = RREG32_SMC(PM_I_CNTL_1);
	value &= ~SCLK_DPM_MASK;
	value |= SCLK_DPM(ni);
	WREG32_SMC(PM_I_CNTL_1, value);
}