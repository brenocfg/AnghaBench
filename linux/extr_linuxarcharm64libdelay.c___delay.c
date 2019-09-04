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
typedef  unsigned long const cycles_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_TIMER_EVT_STREAM_PERIOD_US ; 
 unsigned long USECS_TO_CYCLES (int /*<<< orphan*/ ) ; 
 scalar_t__ arch_timer_evtstrm_available () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long const get_cycles () ; 
 int /*<<< orphan*/  wfe () ; 

void __delay(unsigned long cycles)
{
	cycles_t start = get_cycles();

	if (arch_timer_evtstrm_available()) {
		const cycles_t timer_evt_period =
			USECS_TO_CYCLES(ARCH_TIMER_EVT_STREAM_PERIOD_US);

		while ((get_cycles() - start + timer_evt_period) < cycles)
			wfe();
	}

	while ((get_cycles() - start) < cycles)
		cpu_relax();
}