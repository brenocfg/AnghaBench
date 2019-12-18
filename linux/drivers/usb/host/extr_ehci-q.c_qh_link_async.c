#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; scalar_t__ unlink_reason; scalar_t__ xacterrs; TYPE_2__* hw; TYPE_1__ qh_next; int /*<<< orphan*/  clearing_tt; int /*<<< orphan*/  qh_dma; } ;
struct ehci_hcd {struct ehci_qh* async; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_4__ {int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  QH_NEXT (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ QH_STATE_IDLE ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  enable_async (struct ehci_hcd*) ; 
 int /*<<< orphan*/  qh_refresh (struct ehci_hcd*,struct ehci_qh*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void qh_link_async (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	__hc32		dma = QH_NEXT(ehci, qh->qh_dma);
	struct ehci_qh	*head;

	/* Don't link a QH if there's a Clear-TT-Buffer pending */
	if (unlikely(qh->clearing_tt))
		return;

	WARN_ON(qh->qh_state != QH_STATE_IDLE);

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	qh_refresh(ehci, qh);

	/* splice right after start */
	head = ehci->async;
	qh->qh_next = head->qh_next;
	qh->hw->hw_next = head->hw->hw_next;
	wmb ();

	head->qh_next.qh = qh;
	head->hw->hw_next = dma;

	qh->qh_state = QH_STATE_LINKED;
	qh->xacterrs = 0;
	qh->unlink_reason = 0;
	/* qtd completions reported later by interrupt */

	enable_async(ehci);
}