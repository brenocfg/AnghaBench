#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sumo_ps {int num_levels; int flags; TYPE_1__* levels; } ;
struct TYPE_4__ {int sclk; } ;
struct sumo_power_info {int /*<<< orphan*/  psp; int /*<<< orphan*/  dsp; TYPE_2__ boost_pl; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {int sclk; } ;

/* Variables and functions */
 int BOOST_DPM_LEVEL ; 
 scalar_t__ CG_BSP_0 ; 
 int SUMO_POWERSTATE_FLAGS_BOOST_STATE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sumo_calculate_bsp (struct radeon_device*,int) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void sumo_program_bsp(struct radeon_device *rdev,
			     struct radeon_ps *rps)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct sumo_ps *ps = sumo_get_ps(rps);
	u32 i;
	u32 highest_engine_clock = ps->levels[ps->num_levels - 1].sclk;

	if (ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		highest_engine_clock = pi->boost_pl.sclk;

	sumo_calculate_bsp(rdev, highest_engine_clock);

	for (i = 0; i < ps->num_levels - 1; i++)
		WREG32(CG_BSP_0 + (i * 4), pi->dsp);

	WREG32(CG_BSP_0 + (i * 4), pi->psp);

	if (ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		WREG32(CG_BSP_0 + (BOOST_DPM_LEVEL * 4), pi->psp);
}