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
struct tc35815_local {TYPE_3__* tfd_base; TYPE_1__* tx_skbs; int /*<<< orphan*/  pci_dev; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  FDSystem; } ;
struct TYPE_6__ {TYPE_2__ fd; } ;
struct TYPE_4__ {scalar_t__ skb_dma; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_FD_NUM ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  panic_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tc35815_init_queues (struct net_device*) ; 

__attribute__((used)) static void
tc35815_clear_queues(struct net_device *dev)
{
	struct tc35815_local *lp = netdev_priv(dev);
	int i;

	for (i = 0; i < TX_FD_NUM; i++) {
		u32 fdsystem = le32_to_cpu(lp->tfd_base[i].fd.FDSystem);
		struct sk_buff *skb =
			fdsystem != 0xffffffff ?
			lp->tx_skbs[fdsystem].skb : NULL;
#ifdef DEBUG
		if (lp->tx_skbs[i].skb != skb) {
			printk("%s: tx_skbs mismatch(%d).\n", dev->name, i);
			panic_queues(dev);
		}
#else
		BUG_ON(lp->tx_skbs[i].skb != skb);
#endif
		if (skb) {
			pci_unmap_single(lp->pci_dev, lp->tx_skbs[i].skb_dma, skb->len, PCI_DMA_TODEVICE);
			lp->tx_skbs[i].skb = NULL;
			lp->tx_skbs[i].skb_dma = 0;
			dev_kfree_skb_any(skb);
		}
		lp->tfd_base[i].fd.FDSystem = cpu_to_le32(0xffffffff);
	}

	tc35815_init_queues(dev);
}