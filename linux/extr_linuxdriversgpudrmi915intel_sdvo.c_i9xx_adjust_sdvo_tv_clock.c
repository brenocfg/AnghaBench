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
struct dpll {int p1; int p2; int n; int m1; int m2; } ;
struct intel_crtc_state {unsigned int port_clock; int clock_set; struct dpll dpll; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 

__attribute__((used)) static void i9xx_adjust_sdvo_tv_clock(struct intel_crtc_state *pipe_config)
{
	unsigned dotclock = pipe_config->port_clock;
	struct dpll *clock = &pipe_config->dpll;

	/*
	 * SDVO TV has fixed PLL values depend on its clock range,
	 * this mirrors vbios setting.
	 */
	if (dotclock >= 100000 && dotclock < 140500) {
		clock->p1 = 2;
		clock->p2 = 10;
		clock->n = 3;
		clock->m1 = 16;
		clock->m2 = 8;
	} else if (dotclock >= 140500 && dotclock <= 200000) {
		clock->p1 = 1;
		clock->p2 = 10;
		clock->n = 6;
		clock->m1 = 12;
		clock->m2 = 8;
	} else {
		WARN(1, "SDVO TV clock out of range: %i\n", dotclock);
	}

	pipe_config->clock_set = true;
}