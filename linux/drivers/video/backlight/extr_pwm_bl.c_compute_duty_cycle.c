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
typedef  unsigned int u64 ;
struct pwm_state {unsigned int period; } ;
struct pwm_bl_data {unsigned int lth_brightness; unsigned int* levels; int /*<<< orphan*/  scale; int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_get_state (int /*<<< orphan*/ ,struct pwm_state*) ; 

__attribute__((used)) static int compute_duty_cycle(struct pwm_bl_data *pb, int brightness)
{
	unsigned int lth = pb->lth_brightness;
	struct pwm_state state;
	u64 duty_cycle;

	pwm_get_state(pb->pwm, &state);

	if (pb->levels)
		duty_cycle = pb->levels[brightness];
	else
		duty_cycle = brightness;

	duty_cycle *= state.period - lth;
	do_div(duty_cycle, pb->scale);

	return duty_cycle + lth;
}