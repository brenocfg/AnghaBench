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
struct sumo_ps {int num_levels; int flags; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int BOOST_DPM_LEVEL ; 
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_4 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SUMO_POWERSTATE_FLAGS_BOOST_STATE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void sumo_program_wl(struct radeon_device *rdev,
			    struct radeon_ps *rps)
{
	struct sumo_ps *new_ps = sumo_get_ps(rps);
	u32 dpm_ctrl4 = RREG32(CG_SCLK_DPM_CTRL_4);

	dpm_ctrl4 &= 0xFFFFFF00;
	dpm_ctrl4 |= (1 << (new_ps->num_levels - 1));

	if (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		dpm_ctrl4 |= (1 << BOOST_DPM_LEVEL);

	WREG32(CG_SCLK_DPM_CTRL_4, dpm_ctrl4);
}