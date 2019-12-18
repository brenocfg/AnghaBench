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
 int /*<<< orphan*/  PM_TP ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_UVD_DPM_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int,int,int,int*,int*) ; 
 int radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static void trinity_setup_uvd_dpm_interval(struct radeon_device *rdev,
					   u32 interval)
{
	u32 p, u;
	u32 tp = RREG32_SMC(PM_TP);
	u32 val;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(interval, xclk, 16, &p, &u);

	val = (p + tp - 1) / tp;

	WREG32_SMC(SMU_UVD_DPM_CNTL, val);
}