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
struct sumo_power_info {scalar_t__ thermal_auto_throttling; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_3 ; 
 int GNB_THERMTHRO_MASK ; 
 int GNB_TT (scalar_t__) ; 
 int GNB_TT_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void sumo_program_ttt(struct radeon_device *rdev)
{
	u32 cg_sclk_dpm_ctrl_3 = RREG32(CG_SCLK_DPM_CTRL_3);
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	cg_sclk_dpm_ctrl_3 &= ~(GNB_TT_MASK | GNB_THERMTHRO_MASK);
	cg_sclk_dpm_ctrl_3 |= GNB_TT(pi->thermal_auto_throttling + 49);

	WREG32(CG_SCLK_DPM_CTRL_3, cg_sclk_dpm_ctrl_3);
}