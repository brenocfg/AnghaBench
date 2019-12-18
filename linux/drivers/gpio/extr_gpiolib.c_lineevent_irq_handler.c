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
struct lineevent_state {int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  ktime_get_real_ns () ; 

__attribute__((used)) static irqreturn_t lineevent_irq_handler(int irq, void *p)
{
	struct lineevent_state *le = p;

	/*
	 * Just store the timestamp in hardirq context so we get it as
	 * close in time as possible to the actual event.
	 */
	le->timestamp = ktime_get_real_ns();

	return IRQ_WAKE_THREAD;
}