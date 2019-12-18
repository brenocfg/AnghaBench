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
typedef  int u32 ;
struct oxu_hcd {TYPE_1__* regs; struct ehci_qh* async; } ;
struct TYPE_5__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; int /*<<< orphan*/  hw_next; TYPE_2__ qh_next; int /*<<< orphan*/  qh_dma; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_ASE ; 
 int CMD_RUN ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  QH_NEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ QH_STATE_IDLE ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  STS_ASS ; 
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 int /*<<< orphan*/  handshake (struct oxu_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* oxu_to_hcd (struct oxu_hcd*) ; 
 int /*<<< orphan*/  qh_refresh (struct oxu_hcd*,struct ehci_qh*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_action_done (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qh_link_async(struct oxu_hcd *oxu, struct ehci_qh *qh)
{
	__le32 dma = QH_NEXT(qh->qh_dma);
	struct ehci_qh *head;

	/* (re)start the async schedule? */
	head = oxu->async;
	timer_action_done(oxu, TIMER_ASYNC_OFF);
	if (!head->qh_next.qh) {
		u32	cmd = readl(&oxu->regs->command);

		if (!(cmd & CMD_ASE)) {
			/* in case a clear of CMD_ASE didn't take yet */
			(void)handshake(oxu, &oxu->regs->status,
					STS_ASS, 0, 150);
			cmd |= CMD_ASE | CMD_RUN;
			writel(cmd, &oxu->regs->command);
			oxu_to_hcd(oxu)->state = HC_STATE_RUNNING;
			/* posted write need not be known to HC yet ... */
		}
	}

	/* clear halt and/or toggle; and maybe recover from silicon quirk */
	if (qh->qh_state == QH_STATE_IDLE)
		qh_refresh(oxu, qh);

	/* splice right after start */
	qh->qh_next = head->qh_next;
	qh->hw_next = head->hw_next;
	wmb();

	head->qh_next.qh = qh;
	head->hw_next = dma;

	qh->qh_state = QH_STATE_LINKED;
	/* qtd completions reported later by interrupt */
}