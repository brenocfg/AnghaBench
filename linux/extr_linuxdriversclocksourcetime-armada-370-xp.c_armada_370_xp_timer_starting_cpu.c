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
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {char* name; int features; int shift; int rating; int /*<<< orphan*/  irq; int /*<<< orphan*/  cpumask; void* tick_resume; void* set_state_oneshot; int /*<<< orphan*/  set_state_periodic; void* set_state_shutdown; int /*<<< orphan*/  set_next_event; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int CLOCK_EVT_FEAT_PERIODIC ; 
 int /*<<< orphan*/  TIMER0_25MHZ ; 
 int /*<<< orphan*/  armada_370_xp_clkevt_irq ; 
 int /*<<< orphan*/  armada_370_xp_clkevt_next_event ; 
 int /*<<< orphan*/  armada_370_xp_clkevt_set_periodic ; 
 void* armada_370_xp_clkevt_shutdown ; 
 int /*<<< orphan*/  armada_370_xp_evt ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_timer_ctrl_clrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ timer25Mhz ; 
 int /*<<< orphan*/  timer_clk ; 

__attribute__((used)) static int armada_370_xp_timer_starting_cpu(unsigned int cpu)
{
	struct clock_event_device *evt = per_cpu_ptr(armada_370_xp_evt, cpu);
	u32 clr = 0, set = 0;

	if (timer25Mhz)
		set = TIMER0_25MHZ;
	else
		clr = TIMER0_25MHZ;
	local_timer_ctrl_clrset(clr, set);

	evt->name		= "armada_370_xp_per_cpu_tick",
	evt->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC;
	evt->shift		= 32,
	evt->rating		= 300,
	evt->set_next_event	= armada_370_xp_clkevt_next_event,
	evt->set_state_shutdown	= armada_370_xp_clkevt_shutdown;
	evt->set_state_periodic	= armada_370_xp_clkevt_set_periodic;
	evt->set_state_oneshot	= armada_370_xp_clkevt_shutdown;
	evt->tick_resume	= armada_370_xp_clkevt_shutdown;
	evt->irq		= armada_370_xp_clkevt_irq;
	evt->cpumask		= cpumask_of(cpu);

	clockevents_config_and_register(evt, timer_clk, 1, 0xfffffffe);
	enable_percpu_irq(evt->irq, 0);

	return 0;
}