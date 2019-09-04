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
struct sumo_power_info {scalar_t__ enable_sclk_ds; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_11 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void sumo_set_ss_dividers(struct radeon_device *rdev,
				 u32 index, u32 divider)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	if (pi->enable_sclk_ds) {
		u32 dpm_ctrl = RREG32(CG_SCLK_DPM_CTRL_11);

		dpm_ctrl &= ~(0x7 << (index * 3));
		dpm_ctrl |= (divider << (index * 3));
		WREG32(CG_SCLK_DPM_CTRL_11, dpm_ctrl);
	}
}