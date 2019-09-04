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
struct clock_event_device {char* name; int rating; int /*<<< orphan*/  set_next_event; int /*<<< orphan*/  set_state_oneshot; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  hv_ce_set_next_event ; 
 int /*<<< orphan*/  hv_ce_set_oneshot ; 
 int /*<<< orphan*/  hv_ce_shutdown ; 

__attribute__((used)) static void hv_init_clockevent_device(struct clock_event_device *dev, int cpu)
{
	dev->name = "Hyper-V clockevent";
	dev->features = CLOCK_EVT_FEAT_ONESHOT;
	dev->cpumask = cpumask_of(cpu);
	dev->rating = 1000;
	/*
	 * Avoid settint dev->owner = THIS_MODULE deliberately as doing so will
	 * result in clockevents_config_and_register() taking additional
	 * references to the hv_vmbus module making it impossible to unload.
	 */

	dev->set_state_shutdown = hv_ce_shutdown;
	dev->set_state_oneshot = hv_ce_set_oneshot;
	dev->set_next_event = hv_ce_set_next_event;
}