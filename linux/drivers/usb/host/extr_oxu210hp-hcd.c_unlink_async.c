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
struct oxu_hcd {struct ehci_qh* reclaim; } ;
struct ehci_qh {scalar_t__ qh_state; struct ehci_qh* reclaim; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 scalar_t__ QH_STATE_LINKED ; 
 scalar_t__ QH_STATE_UNLINK_WAIT ; 
 int /*<<< orphan*/  end_unlink_async (struct oxu_hcd*) ; 
 TYPE_1__* oxu_to_hcd (struct oxu_hcd*) ; 
 int /*<<< orphan*/  start_unlink_async (struct oxu_hcd*,struct ehci_qh*) ; 

__attribute__((used)) static void unlink_async(struct oxu_hcd *oxu, struct ehci_qh *qh)
{
	/* if we need to use IAA and it's busy, defer */
	if (qh->qh_state == QH_STATE_LINKED
			&& oxu->reclaim
			&& HC_IS_RUNNING(oxu_to_hcd(oxu)->state)) {
		struct ehci_qh		*last;

		for (last = oxu->reclaim;
				last->reclaim;
				last = last->reclaim)
			continue;
		qh->qh_state = QH_STATE_UNLINK_WAIT;
		last->reclaim = qh;

	/* bypass IAA if the hc can't care */
	} else if (!HC_IS_RUNNING(oxu_to_hcd(oxu)->state) && oxu->reclaim)
		end_unlink_async(oxu);

	/* something else might have unlinked the qh by now */
	if (qh->qh_state == QH_STATE_LINKED)
		start_unlink_async(oxu, qh);
}