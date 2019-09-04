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
struct tsc200x {int /*<<< orphan*/  irq; int /*<<< orphan*/  esd_work; int /*<<< orphan*/  penup_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc200x_stop_scan (struct tsc200x*) ; 

__attribute__((used)) static void __tsc200x_disable(struct tsc200x *ts)
{
	tsc200x_stop_scan(ts);

	disable_irq(ts->irq);
	del_timer_sync(&ts->penup_timer);

	cancel_delayed_work_sync(&ts->esd_work);

	enable_irq(ts->irq);
}