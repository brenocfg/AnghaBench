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
struct ehci_qh {scalar_t__ qh_state; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  single_unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  start_iaa_cycle (struct ehci_hcd*) ; 

__attribute__((used)) static void start_unlink_async(struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	/* If the QH isn't linked then there's nothing we can do. */
	if (qh->qh_state != QH_STATE_LINKED)
		return;

	single_unlink_async(ehci, qh);
	start_iaa_cycle(ehci);
}