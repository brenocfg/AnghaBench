#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct thermal_zone_device {scalar_t__ temperature; int /*<<< orphan*/  passive_delay; TYPE_1__* tzp; struct power_allocator_params* governor_data; } ;
struct power_allocator_params {scalar_t__ err_integral; scalar_t__ prev_err; int /*<<< orphan*/  trip_switch_on; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ sustainable_power; scalar_t__ integral_cutoff; int /*<<< orphan*/  k_d; int /*<<< orphan*/  k_i; int /*<<< orphan*/  k_pu; int /*<<< orphan*/  k_po; } ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__ clamp (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ div_frac (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estimate_pid_constants (struct thermal_zone_device*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ estimate_sustainable_power (struct thermal_zone_device*) ; 
 scalar_t__ frac_to_int (scalar_t__) ; 
 scalar_t__ int_to_frac (scalar_t__) ; 
 scalar_t__ mul_frac (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_thermal_power_allocator_pid (struct thermal_zone_device*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u32 pid_controller(struct thermal_zone_device *tz,
			  int control_temp,
			  u32 max_allocatable_power)
{
	s64 p, i, d, power_range;
	s32 err, max_power_frac;
	u32 sustainable_power;
	struct power_allocator_params *params = tz->governor_data;

	max_power_frac = int_to_frac(max_allocatable_power);

	if (tz->tzp->sustainable_power) {
		sustainable_power = tz->tzp->sustainable_power;
	} else {
		sustainable_power = estimate_sustainable_power(tz);
		estimate_pid_constants(tz, sustainable_power,
				       params->trip_switch_on, control_temp,
				       true);
	}

	err = control_temp - tz->temperature;
	err = int_to_frac(err);

	/* Calculate the proportional term */
	p = mul_frac(err < 0 ? tz->tzp->k_po : tz->tzp->k_pu, err);

	/*
	 * Calculate the integral term
	 *
	 * if the error is less than cut off allow integration (but
	 * the integral is limited to max power)
	 */
	i = mul_frac(tz->tzp->k_i, params->err_integral);

	if (err < int_to_frac(tz->tzp->integral_cutoff)) {
		s64 i_next = i + mul_frac(tz->tzp->k_i, err);

		if (abs(i_next) < max_power_frac) {
			i = i_next;
			params->err_integral += err;
		}
	}

	/*
	 * Calculate the derivative term
	 *
	 * We do err - prev_err, so with a positive k_d, a decreasing
	 * error (i.e. driving closer to the line) results in less
	 * power being applied, slowing down the controller)
	 */
	d = mul_frac(tz->tzp->k_d, err - params->prev_err);
	d = div_frac(d, tz->passive_delay);
	params->prev_err = err;

	power_range = p + i + d;

	/* feed-forward the known sustainable dissipatable power */
	power_range = sustainable_power + frac_to_int(power_range);

	power_range = clamp(power_range, (s64)0, (s64)max_allocatable_power);

	trace_thermal_power_allocator_pid(tz, frac_to_int(err),
					  frac_to_int(params->err_integral),
					  frac_to_int(p), frac_to_int(i),
					  frac_to_int(d), power_range);

	return power_range;
}