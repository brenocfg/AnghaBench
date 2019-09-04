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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct amd8111e_priv {int tx_idx; int /*<<< orphan*/  lock; scalar_t__ mmio; TYPE_1__* tx_ring; int /*<<< orphan*/ * tx_dma_addr; int /*<<< orphan*/  pci_dev; struct sk_buff** tx_skbuff; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_flags; int /*<<< orphan*/  buff_phy_addr; int /*<<< orphan*/  buff_count; } ;

/* Variables and functions */
 int ADD_FCS_BIT ; 
 scalar_t__ CMD0 ; 
 int ENP_BIT ; 
 int LTINT_BIT ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int OWN_BIT ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int RDMD0 ; 
 int STP_BIT ; 
 int TDMD0 ; 
 int TX_RING_DR_MOD_MASK ; 
 int VAL1 ; 
 int VAL2 ; 
 scalar_t__ amd8111e_tx_queue_avail (struct amd8111e_priv*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t amd8111e_start_xmit(struct sk_buff *skb,
				       struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	int tx_index;
	unsigned long flags;

	spin_lock_irqsave(&lp->lock, flags);

	tx_index = lp->tx_idx & TX_RING_DR_MOD_MASK;

	lp->tx_ring[tx_index].buff_count = cpu_to_le16(skb->len);

	lp->tx_skbuff[tx_index] = skb;
	lp->tx_ring[tx_index].tx_flags = 0;

#if AMD8111E_VLAN_TAG_USED
	if (skb_vlan_tag_present(skb)) {
		lp->tx_ring[tx_index].tag_ctrl_cmd |=
				cpu_to_le16(TCC_VLAN_INSERT);
		lp->tx_ring[tx_index].tag_ctrl_info =
				cpu_to_le16(skb_vlan_tag_get(skb));

	}
#endif
	lp->tx_dma_addr[tx_index] =
	    pci_map_single(lp->pci_dev, skb->data, skb->len, PCI_DMA_TODEVICE);
	lp->tx_ring[tx_index].buff_phy_addr =
	    cpu_to_le32(lp->tx_dma_addr[tx_index]);

	/*  Set FCS and LTINT bits */
	wmb();
	lp->tx_ring[tx_index].tx_flags |=
	    cpu_to_le16(OWN_BIT | STP_BIT | ENP_BIT|ADD_FCS_BIT|LTINT_BIT);

	lp->tx_idx++;

	/* Trigger an immediate send poll. */
	writel( VAL1 | TDMD0, lp->mmio + CMD0);
	writel( VAL2 | RDMD0,lp->mmio + CMD0);

	if(amd8111e_tx_queue_avail(lp) < 0){
		netif_stop_queue(dev);
	}
	spin_unlock_irqrestore(&lp->lock, flags);
	return NETDEV_TX_OK;
}