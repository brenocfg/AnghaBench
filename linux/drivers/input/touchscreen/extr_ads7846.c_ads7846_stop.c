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
struct ads7846 {int stopped; TYPE_1__* spi; int /*<<< orphan*/  wait; int /*<<< orphan*/  suspended; int /*<<< orphan*/  disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ads7846_stop(struct ads7846 *ts)
{
	if (!ts->disabled && !ts->suspended) {
		/* Signal IRQ thread to stop polling and disable the handler. */
		ts->stopped = true;
		mb();
		wake_up(&ts->wait);
		disable_irq(ts->spi->irq);
	}
}