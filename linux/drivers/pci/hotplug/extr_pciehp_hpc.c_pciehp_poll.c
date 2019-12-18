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
struct controller {int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IRQ_NOTCONNECTED ; 
 scalar_t__ IRQ_WAKE_THREAD ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 scalar_t__ pciehp_isr (int /*<<< orphan*/ ,struct controller*) ; 
 int /*<<< orphan*/  pciehp_ist (int /*<<< orphan*/ ,struct controller*) ; 
 int pciehp_poll_time ; 
 int /*<<< orphan*/  schedule_timeout_idle (int) ; 

__attribute__((used)) static int pciehp_poll(void *data)
{
	struct controller *ctrl = data;

	schedule_timeout_idle(10 * HZ); /* start with 10 sec delay */

	while (!kthread_should_stop()) {
		/* poll for interrupt events or user requests */
		while (pciehp_isr(IRQ_NOTCONNECTED, ctrl) == IRQ_WAKE_THREAD ||
		       atomic_read(&ctrl->pending_events))
			pciehp_ist(IRQ_NOTCONNECTED, ctrl);

		if (pciehp_poll_time <= 0 || pciehp_poll_time > 60)
			pciehp_poll_time = 2; /* clamp to sane value */

		schedule_timeout_idle(pciehp_poll_time * HZ);
	}

	return 0;
}