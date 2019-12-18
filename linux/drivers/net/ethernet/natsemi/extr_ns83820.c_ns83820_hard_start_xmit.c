#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {scalar_t__ ip_summed; unsigned int len; int /*<<< orphan*/  data; scalar_t__ data_len; } ;
struct ns83820 {int CFG_cache; int tx_free_idx; unsigned int tx_done_idx; int tx_intr_idx; int tx_phy_descs; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  nr_tx_skbs; struct sk_buff** tx_skbs; TYPE_5__* pci_dev; int /*<<< orphan*/ * tx_descs; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_10__ {scalar_t__ protocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 int CFG_LNKSTS ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CMDSTS_INTR ; 
 int CMDSTS_MORE ; 
 int CMDSTS_OWN ; 
 int DESC_BUFPTR ; 
 size_t DESC_CMDSTS ; 
 size_t DESC_EXTSTS ; 
 size_t DESC_LINK ; 
 int DESC_SIZE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EXTSTS_IPPKT ; 
 int EXTSTS_TCPPKT ; 
 int EXTSTS_UDPPKT ; 
 int EXTSTS_VPKT ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int MIN_TX_DESC_FREE ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 unsigned int NR_TX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  volatile cpu_to_le32 (int) ; 
 int /*<<< orphan*/  desc_addr_set (int /*<<< orphan*/  volatile*,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int htons (short) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kick_tx (struct ns83820*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ page_to_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_map_single (TYPE_5__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (TYPE_1__*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 short skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ start_tx_okay (struct ns83820*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t ns83820_hard_start_xmit(struct sk_buff *skb,
					   struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	u32 free_idx, cmdsts, extsts;
	int nr_free, nr_frags;
	unsigned tx_done_idx, last_idx;
	dma_addr_t buf;
	unsigned len;
	skb_frag_t *frag;
	int stopped = 0;
	int do_intr = 0;
	volatile __le32 *first_desc;

	dprintk("ns83820_hard_start_xmit\n");

	nr_frags =  skb_shinfo(skb)->nr_frags;
again:
	if (unlikely(dev->CFG_cache & CFG_LNKSTS)) {
		netif_stop_queue(ndev);
		if (unlikely(dev->CFG_cache & CFG_LNKSTS))
			return NETDEV_TX_BUSY;
		netif_start_queue(ndev);
	}

	last_idx = free_idx = dev->tx_free_idx;
	tx_done_idx = dev->tx_done_idx;
	nr_free = (tx_done_idx + NR_TX_DESC-2 - free_idx) % NR_TX_DESC;
	nr_free -= 1;
	if (nr_free <= nr_frags) {
		dprintk("stop_queue - not enough(%p)\n", ndev);
		netif_stop_queue(ndev);

		/* Check again: we may have raced with a tx done irq */
		if (dev->tx_done_idx != tx_done_idx) {
			dprintk("restart queue(%p)\n", ndev);
			netif_start_queue(ndev);
			goto again;
		}
		return NETDEV_TX_BUSY;
	}

	if (free_idx == dev->tx_intr_idx) {
		do_intr = 1;
		dev->tx_intr_idx = (dev->tx_intr_idx + NR_TX_DESC/4) % NR_TX_DESC;
	}

	nr_free -= nr_frags;
	if (nr_free < MIN_TX_DESC_FREE) {
		dprintk("stop_queue - last entry(%p)\n", ndev);
		netif_stop_queue(ndev);
		stopped = 1;
	}

	frag = skb_shinfo(skb)->frags;
	if (!nr_frags)
		frag = NULL;
	extsts = 0;
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		extsts |= EXTSTS_IPPKT;
		if (IPPROTO_TCP == ip_hdr(skb)->protocol)
			extsts |= EXTSTS_TCPPKT;
		else if (IPPROTO_UDP == ip_hdr(skb)->protocol)
			extsts |= EXTSTS_UDPPKT;
	}

#ifdef NS83820_VLAN_ACCEL_SUPPORT
	if (skb_vlan_tag_present(skb)) {
		/* fetch the vlan tag info out of the
		 * ancillary data if the vlan code
		 * is using hw vlan acceleration
		 */
		short tag = skb_vlan_tag_get(skb);
		extsts |= (EXTSTS_VPKT | htons(tag));
	}
#endif

	len = skb->len;
	if (nr_frags)
		len -= skb->data_len;
	buf = pci_map_single(dev->pci_dev, skb->data, len, PCI_DMA_TODEVICE);

	first_desc = dev->tx_descs + (free_idx * DESC_SIZE);

	for (;;) {
		volatile __le32 *desc = dev->tx_descs + (free_idx * DESC_SIZE);

		dprintk("frag[%3u]: %4u @ 0x%08Lx\n", free_idx, len,
			(unsigned long long)buf);
		last_idx = free_idx;
		free_idx = (free_idx + 1) % NR_TX_DESC;
		desc[DESC_LINK] = cpu_to_le32(dev->tx_phy_descs + (free_idx * DESC_SIZE * 4));
		desc_addr_set(desc + DESC_BUFPTR, buf);
		desc[DESC_EXTSTS] = cpu_to_le32(extsts);

		cmdsts = ((nr_frags) ? CMDSTS_MORE : do_intr ? CMDSTS_INTR : 0);
		cmdsts |= (desc == first_desc) ? 0 : CMDSTS_OWN;
		cmdsts |= len;
		desc[DESC_CMDSTS] = cpu_to_le32(cmdsts);

		if (!nr_frags)
			break;

		buf = skb_frag_dma_map(&dev->pci_dev->dev, frag, 0,
				       skb_frag_size(frag), DMA_TO_DEVICE);
		dprintk("frag: buf=%08Lx  page=%08lx offset=%08lx\n",
			(long long)buf, (long) page_to_pfn(frag->page),
			frag->page_offset);
		len = skb_frag_size(frag);
		frag++;
		nr_frags--;
	}
	dprintk("done pkt\n");

	spin_lock_irq(&dev->tx_lock);
	dev->tx_skbs[last_idx] = skb;
	first_desc[DESC_CMDSTS] |= cpu_to_le32(CMDSTS_OWN);
	dev->tx_free_idx = free_idx;
	atomic_inc(&dev->nr_tx_skbs);
	spin_unlock_irq(&dev->tx_lock);

	kick_tx(dev);

	/* Check again: we may have raced with a tx done irq */
	if (stopped && (dev->tx_done_idx != tx_done_idx) && start_tx_okay(dev))
		netif_start_queue(ndev);

	return NETDEV_TX_OK;
}