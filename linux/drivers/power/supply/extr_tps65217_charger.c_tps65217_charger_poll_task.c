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

/* Variables and functions */
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  tps65217_charger_irq (int,void*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int tps65217_charger_poll_task(void *data)
{
	set_freezable();

	while (!kthread_should_stop()) {
		schedule_timeout_interruptible(POLL_INTERVAL);
		try_to_freeze();
		tps65217_charger_irq(-1, data);
	}
	return 0;
}