#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long expires; } ;
struct oxu_hcd {TYPE_1__ watchdog; int /*<<< orphan*/  actions; } ;
typedef  enum ehci_timer_action { ____Placeholder_ehci_timer_action } ehci_timer_action ;

/* Variables and functions */
 unsigned long EHCI_ASYNC_JIFFIES ; 
 unsigned long EHCI_IAA_JIFFIES ; 
 unsigned long EHCI_IO_JIFFIES ; 
 unsigned long EHCI_SHRINK_JIFFIES ; 
#define  TIMER_ASYNC_OFF 131 
#define  TIMER_ASYNC_SHRINK 130 
#define  TIMER_IAA_WATCHDOG 129 
#define  TIMER_IO_WATCHDOG 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

__attribute__((used)) static inline void timer_action(struct oxu_hcd *oxu,
					enum ehci_timer_action action)
{
	if (!test_and_set_bit(action, &oxu->actions)) {
		unsigned long t;

		switch (action) {
		case TIMER_IAA_WATCHDOG:
			t = EHCI_IAA_JIFFIES;
			break;
		case TIMER_IO_WATCHDOG:
			t = EHCI_IO_JIFFIES;
			break;
		case TIMER_ASYNC_OFF:
			t = EHCI_ASYNC_JIFFIES;
			break;
		case TIMER_ASYNC_SHRINK:
		default:
			t = EHCI_SHRINK_JIFFIES;
			break;
		}
		t += jiffies;
		/* all timings except IAA watchdog can be overridden.
		 * async queue SHRINK often precedes IAA.  while it's ready
		 * to go OFF neither can matter, and afterwards the IO
		 * watchdog stops unless there's still periodic traffic.
		 */
		if (action != TIMER_IAA_WATCHDOG
				&& t > oxu->watchdog.expires
				&& timer_pending(&oxu->watchdog))
			return;
		mod_timer(&oxu->watchdog, t);
	}
}