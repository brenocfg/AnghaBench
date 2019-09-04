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
struct rv7xx_power_info {scalar_t__ mgcgtssm; } ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGTS_SM_CTRL_REG ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_0 ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_1 ; 
 scalar_t__ CHIP_RV770 ; 
 int RV770_MGCGCGTSSMCTRL_DFLT ; 
 int RV770_MGCGTTLOCAL0_DFLT ; 
 int RV770_MGCGTTLOCAL1_DFLT ; 
 int RV7XX_MGCGTTLOCAL0_DFLT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv770_mg_clock_gating_enable(struct radeon_device *rdev,
					 bool enable)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	if (enable) {
		u32 mgcg_cgtt_local0;

		if (rdev->family == CHIP_RV770)
			mgcg_cgtt_local0 = RV770_MGCGTTLOCAL0_DFLT;
		else
			mgcg_cgtt_local0 = RV7XX_MGCGTTLOCAL0_DFLT;

		WREG32(CG_CGTT_LOCAL_0, mgcg_cgtt_local0);
		WREG32(CG_CGTT_LOCAL_1, (RV770_MGCGTTLOCAL1_DFLT & 0xFFFFCFFF));

		if (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, RV770_MGCGCGTSSMCTRL_DFLT);
	} else {
		WREG32(CG_CGTT_LOCAL_0, 0xFFFFFFFF);
		WREG32(CG_CGTT_LOCAL_1, 0xFFFFCFFF);
	}
}