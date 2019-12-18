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
struct TYPE_4__ {int cntinfo; } ;
struct sgiseeq_tx_desc {int /*<<< orphan*/ * skb; TYPE_2__ tdma; } ;
struct sgiseeq_regs {int dummy; } ;
struct sgiseeq_private {int tx_old; int tx_new; struct sgiseeq_tx_desc* tx_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct hpc3_ethregs {unsigned long tx_ctrl; int /*<<< orphan*/  tx_ndptr; } ;

/* Variables and functions */
 unsigned long HPC3_ETXCTRL_ACTIVE ; 
 int HPCDMA_EOX ; 
 int HPCDMA_ETXD ; 
 int HPCDMA_XIE ; 
 int HPCDMA_XIU ; 
 void* NEXT_TX (int) ; 
 unsigned long SEEQ_TSTAT_LCLS ; 
 unsigned long SEEQ_TSTAT_PTRANS ; 
 unsigned long SEEQ_TSTAT_R16 ; 
 unsigned long SEEQ_TSTAT_UFLOW ; 
 int /*<<< orphan*/  VIRT_TO_DMA (struct sgiseeq_private*,struct sgiseeq_tx_desc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_desc_cpu (struct net_device*,struct sgiseeq_tx_desc*) ; 
 int /*<<< orphan*/  dma_sync_desc_dev (struct net_device*,struct sgiseeq_tx_desc*) ; 
 int /*<<< orphan*/  tx_maybe_reset_collisions (struct sgiseeq_private*,struct sgiseeq_regs*) ; 

__attribute__((used)) static inline void sgiseeq_tx(struct net_device *dev, struct sgiseeq_private *sp,
			      struct hpc3_ethregs *hregs,
			      struct sgiseeq_regs *sregs)
{
	struct sgiseeq_tx_desc *td;
	unsigned long status = hregs->tx_ctrl;
	int j;

	tx_maybe_reset_collisions(sp, sregs);

	if (!(status & (HPC3_ETXCTRL_ACTIVE | SEEQ_TSTAT_PTRANS))) {
		/* Oops, HPC detected some sort of error. */
		if (status & SEEQ_TSTAT_R16)
			dev->stats.tx_aborted_errors++;
		if (status & SEEQ_TSTAT_UFLOW)
			dev->stats.tx_fifo_errors++;
		if (status & SEEQ_TSTAT_LCLS)
			dev->stats.collisions++;
	}

	/* Ack 'em... */
	for (j = sp->tx_old; j != sp->tx_new; j = NEXT_TX(j)) {
		td = &sp->tx_desc[j];

		dma_sync_desc_cpu(dev, td);
		if (!(td->tdma.cntinfo & (HPCDMA_XIU)))
			break;
		if (!(td->tdma.cntinfo & (HPCDMA_ETXD))) {
			if (!(status & HPC3_ETXCTRL_ACTIVE)) {
				hregs->tx_ndptr = VIRT_TO_DMA(sp, td);
				hregs->tx_ctrl = HPC3_ETXCTRL_ACTIVE;
			}
			break;
		}
		dev->stats.tx_packets++;
		sp->tx_old = NEXT_TX(sp->tx_old);
		td->tdma.cntinfo &= ~(HPCDMA_XIU | HPCDMA_XIE);
		td->tdma.cntinfo |= HPCDMA_EOX;
		if (td->skb) {
			dev_kfree_skb_any(td->skb);
			td->skb = NULL;
		}
		dma_sync_desc_dev(dev, td);
	}
}