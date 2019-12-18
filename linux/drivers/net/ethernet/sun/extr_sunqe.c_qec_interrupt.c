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
typedef  int u32 ;
struct sunqec {struct sunqe** qes; scalar_t__ gregs; } ;
struct sunqe {int /*<<< orphan*/  lock; scalar_t__ qcregs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CREG_STAT ; 
 int CREG_STAT_ERRORS ; 
 int CREG_STAT_RXIRQ ; 
 int CREG_STAT_TXIRQ ; 
 scalar_t__ CREG_TIMASK ; 
 scalar_t__ GLOB_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TX_BUFFS_AVAIL (struct sunqe*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ qe_is_bolixed (struct sunqe*,int) ; 
 int /*<<< orphan*/  qe_rx (struct sunqe*) ; 
 int /*<<< orphan*/  qe_tx_reclaim (struct sunqe*) ; 
 int sbus_readl (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t qec_interrupt(int irq, void *dev_id)
{
	struct sunqec *qecp = dev_id;
	u32 qec_status;
	int channel = 0;

	/* Latch the status now. */
	qec_status = sbus_readl(qecp->gregs + GLOB_STAT);
	while (channel < 4) {
		if (qec_status & 0xf) {
			struct sunqe *qep = qecp->qes[channel];
			u32 qe_status;

			qe_status = sbus_readl(qep->qcregs + CREG_STAT);
			if (qe_status & CREG_STAT_ERRORS) {
				if (qe_is_bolixed(qep, qe_status))
					goto next;
			}
			if (qe_status & CREG_STAT_RXIRQ)
				qe_rx(qep);
			if (netif_queue_stopped(qep->dev) &&
			    (qe_status & CREG_STAT_TXIRQ)) {
				spin_lock(&qep->lock);
				qe_tx_reclaim(qep);
				if (TX_BUFFS_AVAIL(qep) > 0) {
					/* Wake net queue and return to
					 * lazy tx reclaim.
					 */
					netif_wake_queue(qep->dev);
					sbus_writel(1, qep->qcregs + CREG_TIMASK);
				}
				spin_unlock(&qep->lock);
			}
	next:
			;
		}
		qec_status >>= 4;
		channel++;
	}

	return IRQ_HANDLED;
}