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
struct ehci_hcd {scalar_t__ rh_state; int enabled_hrtimer_events; scalar_t__ isoc_count; scalar_t__ async_count; scalar_t__ intr_count; scalar_t__ need_io_watchdog; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EHCI_HRTIMER_IO_WATCHDOG ; 
 scalar_t__ EHCI_RH_RUNNING ; 
 int /*<<< orphan*/  ehci_enable_event (struct ehci_hcd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void turn_on_io_watchdog(struct ehci_hcd *ehci)
{
	/* Not needed if the controller isn't running or it's already enabled */
	if (ehci->rh_state != EHCI_RH_RUNNING ||
			(ehci->enabled_hrtimer_events &
				BIT(EHCI_HRTIMER_IO_WATCHDOG)))
		return;

	/*
	 * Isochronous transfers always need the watchdog.
	 * For other sorts we use it only if the flag is set.
	 */
	if (ehci->isoc_count > 0 || (ehci->need_io_watchdog &&
			ehci->async_count + ehci->intr_count > 0))
		ehci_enable_event(ehci, EHCI_HRTIMER_IO_WATCHDOG, true);
}