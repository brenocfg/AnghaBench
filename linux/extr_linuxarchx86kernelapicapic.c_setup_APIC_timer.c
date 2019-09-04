#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {char* name; int features; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  cpumask; } ;
struct TYPE_3__ {int rating; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_DUMMY ; 
 int CLOCK_EVT_FEAT_PERIODIC ; 
 int TSC_DIVISOR ; 
 int /*<<< orphan*/  X86_FEATURE_ARAT ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_DEADLINE_TIMER ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int,int,unsigned long) ; 
 int /*<<< orphan*/  clockevents_register_device (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 TYPE_1__ lapic_clockevent ; 
 int /*<<< orphan*/  lapic_events ; 
 int /*<<< orphan*/  lapic_next_deadline ; 
 int /*<<< orphan*/  memcpy (struct clock_event_device*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ this_cpu_has (int /*<<< orphan*/ ) ; 
 struct clock_event_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int tsc_khz ; 

__attribute__((used)) static void setup_APIC_timer(void)
{
	struct clock_event_device *levt = this_cpu_ptr(&lapic_events);

	if (this_cpu_has(X86_FEATURE_ARAT)) {
		lapic_clockevent.features &= ~CLOCK_EVT_FEAT_C3STOP;
		/* Make LAPIC timer preferrable over percpu HPET */
		lapic_clockevent.rating = 150;
	}

	memcpy(levt, &lapic_clockevent, sizeof(*levt));
	levt->cpumask = cpumask_of(smp_processor_id());

	if (this_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER)) {
		levt->name = "lapic-deadline";
		levt->features &= ~(CLOCK_EVT_FEAT_PERIODIC |
				    CLOCK_EVT_FEAT_DUMMY);
		levt->set_next_event = lapic_next_deadline;
		clockevents_config_and_register(levt,
						tsc_khz * (1000 / TSC_DIVISOR),
						0xF, ~0UL);
	} else
		clockevents_register_device(levt);
}