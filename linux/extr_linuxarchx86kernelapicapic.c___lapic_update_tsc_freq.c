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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int TSC_DIVISOR ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_DEADLINE_TIMER ; 
 int /*<<< orphan*/  clockevents_update_freq (struct clock_event_device*,int) ; 
 int /*<<< orphan*/  lapic_events ; 
 int /*<<< orphan*/  this_cpu_has (int /*<<< orphan*/ ) ; 
 struct clock_event_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int tsc_khz ; 

__attribute__((used)) static void __lapic_update_tsc_freq(void *info)
{
	struct clock_event_device *levt = this_cpu_ptr(&lapic_events);

	if (!this_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		return;

	clockevents_update_freq(levt, tsc_khz * (1000 / TSC_DIVISOR));
}