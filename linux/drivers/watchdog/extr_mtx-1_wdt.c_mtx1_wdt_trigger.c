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
struct TYPE_2__ {int gstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  stop; int /*<<< orphan*/  timer; scalar_t__ queue; int /*<<< orphan*/  gpiod; scalar_t__ running; } ;

/* Variables and functions */
 scalar_t__ MTX1_WDT_INTERVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ mtx1_wdt_device ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void mtx1_wdt_trigger(struct timer_list *unused)
{
	spin_lock(&mtx1_wdt_device.lock);
	if (mtx1_wdt_device.running)
		ticks--;

	/* toggle wdt gpio */
	mtx1_wdt_device.gstate = !mtx1_wdt_device.gstate;
	gpiod_set_value(mtx1_wdt_device.gpiod, mtx1_wdt_device.gstate);

	if (mtx1_wdt_device.queue && ticks)
		mod_timer(&mtx1_wdt_device.timer, jiffies + MTX1_WDT_INTERVAL);
	else
		complete(&mtx1_wdt_device.stop);
	spin_unlock(&mtx1_wdt_device.lock);
}