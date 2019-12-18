#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udc_ep {scalar_t__ halted; } ;
struct timer_list {int dummy; } ;
struct TYPE_5__ {struct udc_ep* ep; } ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 size_t UDC_EPIN_IX ; 
 size_t UDC_EPOUT_IX ; 
 int UDC_POLLSTALL_TIMER_USECONDS ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  on_pollstall_exit ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stop_pollstall_timer ; 
 TYPE_2__* udc ; 
 int /*<<< orphan*/  udc_handle_halt_state (struct udc_ep*) ; 
 TYPE_1__ udc_pollstall_timer ; 
 int /*<<< orphan*/  udc_stall_spinlock ; 

__attribute__((used)) static void udc_pollstall_timer_function(struct timer_list *unused)
{
	struct udc_ep *ep;
	int halted = 0;

	spin_lock_irq(&udc_stall_spinlock);
	/*
	 * only one IN and OUT endpoints are handled
	 * IN poll stall
	 */
	ep = &udc->ep[UDC_EPIN_IX];
	udc_handle_halt_state(ep);
	if (ep->halted)
		halted = 1;
	/* OUT poll stall */
	ep = &udc->ep[UDC_EPOUT_IX];
	udc_handle_halt_state(ep);
	if (ep->halted)
		halted = 1;

	/* setup timer again when still halted */
	if (!stop_pollstall_timer && halted) {
		udc_pollstall_timer.expires = jiffies +
					HZ * UDC_POLLSTALL_TIMER_USECONDS
					/ (1000 * 1000);
		add_timer(&udc_pollstall_timer);
	}
	spin_unlock_irq(&udc_stall_spinlock);

	if (stop_pollstall_timer)
		complete(&on_pollstall_exit);
}