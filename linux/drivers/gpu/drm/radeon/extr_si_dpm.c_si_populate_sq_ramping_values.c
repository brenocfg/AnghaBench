#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_ps {int dummy; } ;
struct TYPE_8__ {scalar_t__ sq_ramping_threshold; } ;
struct TYPE_9__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct ni_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct ni_power_info {int enable_sq_ramping; } ;
struct TYPE_11__ {int levelCount; TYPE_4__* levels; } ;
struct TYPE_10__ {void* SQPowerThrottle_2; void* SQPowerThrottle; } ;
struct TYPE_7__ {scalar_t__ sclk; } ;
typedef  TYPE_5__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int EINVAL ; 
 int LTI_RATIO (int) ; 
 int LTI_RATIO_MASK ; 
 int LTI_RATIO_SHIFT ; 
 int MAX_POWER (int) ; 
 int MAX_POWER_DELTA (int) ; 
 int MAX_POWER_DELTA_MASK ; 
 int MAX_POWER_DELTA_SHIFT ; 
 int MAX_POWER_MASK ; 
 int MAX_POWER_SHIFT ; 
 int MIN_POWER (int) ; 
 int MIN_POWER_MASK ; 
 int MIN_POWER_SHIFT ; 
 int SISLANDS_DPM2_SQ_RAMP_LTI_RATIO ; 
 int SISLANDS_DPM2_SQ_RAMP_MAX_POWER ; 
 int SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA ; 
 int SISLANDS_DPM2_SQ_RAMP_MIN_POWER ; 
 int SISLANDS_DPM2_SQ_RAMP_STI_SIZE ; 
 int STI_SIZE (int) ; 
 int STI_SIZE_MASK ; 
 int STI_SIZE_SHIFT ; 
 void* cpu_to_be32 (int) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static int si_populate_sq_ramping_values(struct radeon_device *rdev,
					 struct radeon_ps *radeon_state,
					 SISLANDS_SMC_SWSTATE *smc_state)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct ni_ps *state = ni_get_ps(radeon_state);
	u32 sq_power_throttle, sq_power_throttle2;
	bool enable_sq_ramping = ni_pi->enable_sq_ramping;
	int i;

	if (state->performance_level_count == 0)
		return -EINVAL;

	if (smc_state->levelCount != state->performance_level_count)
		return -EINVAL;

	if (rdev->pm.dpm.sq_ramping_threshold == 0)
		return -EINVAL;

	if (SISLANDS_DPM2_SQ_RAMP_MAX_POWER > (MAX_POWER_MASK >> MAX_POWER_SHIFT))
		enable_sq_ramping = false;

	if (SISLANDS_DPM2_SQ_RAMP_MIN_POWER > (MIN_POWER_MASK >> MIN_POWER_SHIFT))
		enable_sq_ramping = false;

	if (SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA > (MAX_POWER_DELTA_MASK >> MAX_POWER_DELTA_SHIFT))
		enable_sq_ramping = false;

	if (SISLANDS_DPM2_SQ_RAMP_STI_SIZE > (STI_SIZE_MASK >> STI_SIZE_SHIFT))
		enable_sq_ramping = false;

	if (SISLANDS_DPM2_SQ_RAMP_LTI_RATIO > (LTI_RATIO_MASK >> LTI_RATIO_SHIFT))
		enable_sq_ramping = false;

	for (i = 0; i < state->performance_level_count; i++) {
		sq_power_throttle = 0;
		sq_power_throttle2 = 0;

		if ((state->performance_levels[i].sclk >= rdev->pm.dpm.sq_ramping_threshold) &&
		    enable_sq_ramping) {
			sq_power_throttle |= MAX_POWER(SISLANDS_DPM2_SQ_RAMP_MAX_POWER);
			sq_power_throttle |= MIN_POWER(SISLANDS_DPM2_SQ_RAMP_MIN_POWER);
			sq_power_throttle2 |= MAX_POWER_DELTA(SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA);
			sq_power_throttle2 |= STI_SIZE(SISLANDS_DPM2_SQ_RAMP_STI_SIZE);
			sq_power_throttle2 |= LTI_RATIO(SISLANDS_DPM2_SQ_RAMP_LTI_RATIO);
		} else {
			sq_power_throttle |= MAX_POWER_MASK | MIN_POWER_MASK;
			sq_power_throttle2 |= MAX_POWER_DELTA_MASK | STI_SIZE_MASK | LTI_RATIO_MASK;
		}

		smc_state->levels[i].SQPowerThrottle = cpu_to_be32(sq_power_throttle);
		smc_state->levels[i].SQPowerThrottle_2 = cpu_to_be32(sq_power_throttle2);
	}

	return 0;
}