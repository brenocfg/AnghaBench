#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {char const* name; int rating; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  set_state_periodic; int /*<<< orphan*/  set_state_shutdown; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  features; } ;
struct sh_mtu2_channel {int /*<<< orphan*/  index; TYPE_2__* mtu; struct clock_event_device ced; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_FEAT_PERIODIC ; 
 int /*<<< orphan*/  clockevents_register_device (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_clock_event_resume ; 
 int /*<<< orphan*/  sh_mtu2_clock_event_set_periodic ; 
 int /*<<< orphan*/  sh_mtu2_clock_event_shutdown ; 
 int /*<<< orphan*/  sh_mtu2_clock_event_suspend ; 

__attribute__((used)) static void sh_mtu2_register_clockevent(struct sh_mtu2_channel *ch,
					const char *name)
{
	struct clock_event_device *ced = &ch->ced;

	ced->name = name;
	ced->features = CLOCK_EVT_FEAT_PERIODIC;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_state_shutdown = sh_mtu2_clock_event_shutdown;
	ced->set_state_periodic = sh_mtu2_clock_event_set_periodic;
	ced->suspend = sh_mtu2_clock_event_suspend;
	ced->resume = sh_mtu2_clock_event_resume;

	dev_info(&ch->mtu->pdev->dev, "ch%u: used for clock events\n",
		 ch->index);
	clockevents_register_device(ced);
}