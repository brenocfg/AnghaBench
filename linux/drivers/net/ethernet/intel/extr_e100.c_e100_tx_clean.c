#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nic {struct net_device* netdev; int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  cbs_avail; int /*<<< orphan*/  pdev; scalar_t__ cbs; struct cb* cb_to_clean; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_8__ {TYPE_2__ tbd; } ;
struct TYPE_9__ {TYPE_3__ tcb; } ;
struct cb {int status; TYPE_5__* skb; TYPE_4__ u; struct cb* next; } ;
struct TYPE_10__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  cb_complete ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_5__*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int e100_tx_clean(struct nic *nic)
{
	struct net_device *dev = nic->netdev;
	struct cb *cb;
	int tx_cleaned = 0;

	spin_lock(&nic->cb_lock);

	/* Clean CBs marked complete */
	for (cb = nic->cb_to_clean;
	    cb->status & cpu_to_le16(cb_complete);
	    cb = nic->cb_to_clean = cb->next) {
		dma_rmb(); /* read skb after status */
		netif_printk(nic, tx_done, KERN_DEBUG, nic->netdev,
			     "cb[%d]->status = 0x%04X\n",
			     (int)(((void*)cb - (void*)nic->cbs)/sizeof(struct cb)),
			     cb->status);

		if (likely(cb->skb != NULL)) {
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += cb->skb->len;

			pci_unmap_single(nic->pdev,
				le32_to_cpu(cb->u.tcb.tbd.buf_addr),
				le16_to_cpu(cb->u.tcb.tbd.size),
				PCI_DMA_TODEVICE);
			dev_kfree_skb_any(cb->skb);
			cb->skb = NULL;
			tx_cleaned = 1;
		}
		cb->status = 0;
		nic->cbs_avail++;
	}

	spin_unlock(&nic->cb_lock);

	/* Recover from running out of Tx resources in xmit_frame */
	if (unlikely(tx_cleaned && netif_queue_stopped(nic->netdev)))
		netif_wake_queue(nic->netdev);

	return tx_cleaned;
}