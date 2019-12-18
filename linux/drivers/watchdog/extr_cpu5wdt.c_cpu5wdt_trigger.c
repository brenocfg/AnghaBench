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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  timer; scalar_t__ queue; scalar_t__ running; } ;

/* Variables and functions */
 scalar_t__ CPU5WDT_INTERVAL ; 
 scalar_t__ CPU5WDT_TRIGGER_REG ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  cpu5wdt_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 
 int verbose ; 

__attribute__((used)) static void cpu5wdt_trigger(struct timer_list *unused)
{
	if (verbose > 2)
		pr_debug("trigger at %i ticks\n", ticks);

	if (cpu5wdt_device.running)
		ticks--;

	spin_lock(&cpu5wdt_lock);
	/* keep watchdog alive */
	outb(1, port + CPU5WDT_TRIGGER_REG);

	/* requeue?? */
	if (cpu5wdt_device.queue && ticks)
		mod_timer(&cpu5wdt_device.timer, jiffies + CPU5WDT_INTERVAL);
	else {
		/* ticks doesn't matter anyway */
		complete(&cpu5wdt_device.stop);
	}
	spin_unlock(&cpu5wdt_lock);

}