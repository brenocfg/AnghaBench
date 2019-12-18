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
struct oxu_hcd {TYPE_2__* regs; scalar_t__ reclaim_ready; struct ehci_qh* async; struct ehci_qh* reclaim; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; TYPE_1__ qh_next; int /*<<< orphan*/  hw_next; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CMD_ASE ; 
 int CMD_IAAD ; 
 scalar_t__ HC_STATE_HALT ; 
 scalar_t__ QH_STATE_LINKED ; 
 scalar_t__ QH_STATE_UNLINK ; 
 scalar_t__ QH_STATE_UNLINK_WAIT ; 
 int /*<<< orphan*/  TIMER_ASYNC_OFF ; 
 int /*<<< orphan*/  TIMER_IAA_WATCHDOG ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_unlink_async (struct oxu_hcd*) ; 
 TYPE_3__* oxu_to_hcd (struct oxu_hcd*) ; 
 struct ehci_qh* qh_get (struct ehci_qh*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_action (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_action_done (struct oxu_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_unlink_async(struct oxu_hcd *oxu, struct ehci_qh *qh)
{
	int cmd = readl(&oxu->regs->command);
	struct ehci_qh *prev;

#ifdef DEBUG
	assert_spin_locked(&oxu->lock);
	BUG_ON(oxu->reclaim || (qh->qh_state != QH_STATE_LINKED
				&& qh->qh_state != QH_STATE_UNLINK_WAIT));
#endif

	/* stop async schedule right now? */
	if (unlikely(qh == oxu->async)) {
		/* can't get here without STS_ASS set */
		if (oxu_to_hcd(oxu)->state != HC_STATE_HALT
				&& !oxu->reclaim) {
			/* ... and CMD_IAAD clear */
			writel(cmd & ~CMD_ASE, &oxu->regs->command);
			wmb();
			/* handshake later, if we need to */
			timer_action_done(oxu, TIMER_ASYNC_OFF);
		}
		return;
	}

	qh->qh_state = QH_STATE_UNLINK;
	oxu->reclaim = qh = qh_get(qh);

	prev = oxu->async;
	while (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw_next = qh->hw_next;
	prev->qh_next = qh->qh_next;
	wmb();

	if (unlikely(oxu_to_hcd(oxu)->state == HC_STATE_HALT)) {
		/* if (unlikely(qh->reclaim != 0))
		 *	this will recurse, probably not much
		 */
		end_unlink_async(oxu);
		return;
	}

	oxu->reclaim_ready = 0;
	cmd |= CMD_IAAD;
	writel(cmd, &oxu->regs->command);
	(void) readl(&oxu->regs->command);
	timer_action(oxu, TIMER_IAA_WATCHDOG);
}