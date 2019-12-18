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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct cas_tx_desc {int /*<<< orphan*/  control; int /*<<< orphan*/  buffer; } ;
struct cas {int* tx_old; int /*<<< orphan*/ * tx_lock; int /*<<< orphan*/ * stat_lock; TYPE_2__* net_stats; TYPE_1__** tx_tiny_use; int /*<<< orphan*/  pdev; struct net_device* dev; struct sk_buff*** tx_skbs; struct cas_tx_desc** init_txds; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int nr_frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_4__ {int nbufs; scalar_t__ used; } ;

/* Variables and functions */
 int CAS_TABORT (struct cas*) ; 
 int /*<<< orphan*/  CAS_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_BUFFS_AVAIL (struct cas*,int) ; 
 int TX_BUFF_COUNT (int,int,int) ; 
 int /*<<< orphan*/  TX_DESC_BUFLEN ; 
 int TX_DESC_NEXT (int,int) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done ; 

__attribute__((used)) static inline void cas_tx_ringN(struct cas *cp, int ring, int limit)
{
	struct cas_tx_desc *txds;
	struct sk_buff **skbs;
	struct net_device *dev = cp->dev;
	int entry, count;

	spin_lock(&cp->tx_lock[ring]);
	txds = cp->init_txds[ring];
	skbs = cp->tx_skbs[ring];
	entry = cp->tx_old[ring];

	count = TX_BUFF_COUNT(ring, entry, limit);
	while (entry != limit) {
		struct sk_buff *skb = skbs[entry];
		dma_addr_t daddr;
		u32 dlen;
		int frag;

		if (!skb) {
			/* this should never occur */
			entry = TX_DESC_NEXT(ring, entry);
			continue;
		}

		/* however, we might get only a partial skb release. */
		count -= skb_shinfo(skb)->nr_frags +
			+ cp->tx_tiny_use[ring][entry].nbufs + 1;
		if (count < 0)
			break;

		netif_printk(cp, tx_done, KERN_DEBUG, cp->dev,
			     "tx[%d] done, slot %d\n", ring, entry);

		skbs[entry] = NULL;
		cp->tx_tiny_use[ring][entry].nbufs = 0;

		for (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) {
			struct cas_tx_desc *txd = txds + entry;

			daddr = le64_to_cpu(txd->buffer);
			dlen = CAS_VAL(TX_DESC_BUFLEN,
				       le64_to_cpu(txd->control));
			pci_unmap_page(cp->pdev, daddr, dlen,
				       PCI_DMA_TODEVICE);
			entry = TX_DESC_NEXT(ring, entry);

			/* tiny buffer may follow */
			if (cp->tx_tiny_use[ring][entry].used) {
				cp->tx_tiny_use[ring][entry].used = 0;
				entry = TX_DESC_NEXT(ring, entry);
			}
		}

		spin_lock(&cp->stat_lock[ring]);
		cp->net_stats[ring].tx_packets++;
		cp->net_stats[ring].tx_bytes += skb->len;
		spin_unlock(&cp->stat_lock[ring]);
		dev_consume_skb_irq(skb);
	}
	cp->tx_old[ring] = entry;

	/* this is wrong for multiple tx rings. the net device needs
	 * multiple queues for this to do the right thing.  we wait
	 * for 2*packets to be available when using tiny buffers
	 */
	if (netif_queue_stopped(dev) &&
	    (TX_BUFFS_AVAIL(cp, ring) > CAS_TABORT(cp)*(MAX_SKB_FRAGS + 1)))
		netif_wake_queue(dev);
	spin_unlock(&cp->tx_lock[ring]);
}