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
struct sumo_ps {int flags; } ;
struct sumo_power_info {int /*<<< orphan*/  driver_nbps_policy_disable; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_3 ; 
 int /*<<< orphan*/  FORCE_NB_PSTATE_1 ; 
 int SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void sumo_force_nbp_state(struct radeon_device *rdev,
				 struct radeon_ps *rps)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct sumo_ps *new_ps = sumo_get_ps(rps);

	if (!pi->driver_nbps_policy_disable) {
		if (new_ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)
			WREG32_P(CG_SCLK_DPM_CTRL_3, FORCE_NB_PSTATE_1, ~FORCE_NB_PSTATE_1);
		else
			WREG32_P(CG_SCLK_DPM_CTRL_3, 0, ~FORCE_NB_PSTATE_1);
	}
}