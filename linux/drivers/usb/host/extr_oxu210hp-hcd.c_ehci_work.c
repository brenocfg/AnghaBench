#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct oxu_hcd {int scanning; int next_uframe; scalar_t__ periodic_sched; TYPE_2__* async; scalar_t__ reclaim_ready; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_IO_WATCHDOG ; 
 int /*<<< orphan*/  end_unlink_async (struct oxu_hcd*) ; 
 TYPE_3__* oxu_to_hcd (struct oxu_hcd*) ; 
 int /*<<< orphan*/  scan_async (struct oxu_hcd*) ; 
 int /*<<< orphan*/  scan_periodic (struct oxu_hcd*) ; 
 int /*<<< orphan*/  timer_action (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_action_done (struct oxu_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehci_work(struct oxu_hcd *oxu)
{
	timer_action_done(oxu, TIMER_IO_WATCHDOG);
	if (oxu->reclaim_ready)
		end_unlink_async(oxu);

	/* another CPU may drop oxu->lock during a schedule scan while
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	if (oxu->scanning)
		return;
	oxu->scanning = 1;
	scan_async(oxu);
	if (oxu->next_uframe != -1)
		scan_periodic(oxu);
	oxu->scanning = 0;

	/* the IO watchdog guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	if (HC_IS_RUNNING(oxu_to_hcd(oxu)->state) &&
			(oxu->async->qh_next.ptr != NULL ||
			 oxu->periodic_sched != 0))
		timer_action(oxu, TIMER_IO_WATCHDOG);
}