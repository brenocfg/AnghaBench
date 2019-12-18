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
struct pwm_state {unsigned long long duty_cycle; int /*<<< orphan*/  period; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_pwm_calculate_cdty(const struct pwm_state *state,
				     unsigned long cprd, unsigned long *cdty)
{
	unsigned long long cycles = state->duty_cycle;

	cycles *= cprd;
	do_div(cycles, state->period);
	*cdty = cprd - cycles;
}