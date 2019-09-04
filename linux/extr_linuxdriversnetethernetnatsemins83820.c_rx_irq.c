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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct rx_info {unsigned int next_rx; unsigned int next_empty; int /*<<< orphan*/  lock; int /*<<< orphan*/ * descs; int /*<<< orphan*/ * next_rx_desc; struct sk_buff** skbs; int /*<<< orphan*/  up; scalar_t__ phy_descs; } ;
struct ns83820 {int /*<<< orphan*/  pci_dev; struct rx_info rx_info; scalar_t__ base; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  multicast; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int CMDSTS_DEST_MULTI ; 
 int CMDSTS_LEN_MASK ; 
 int CMDSTS_OK ; 
 int CMDSTS_OWN ; 
 int DESC_BUFPTR ; 
 size_t DESC_CMDSTS ; 
 size_t DESC_EXTSTS ; 
 size_t DESC_LINK ; 
 unsigned int DESC_SIZE ; 
 int /*<<< orphan*/  Dprintk (char*,int) ; 
 int NET_RX_DROP ; 
 unsigned int NR_RX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct ns83820* PRIV (struct net_device*) ; 
 scalar_t__ RXDP ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  clear_rx_desc (struct ns83820*,unsigned int) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mb () ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rx_irq(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	struct rx_info *info = &dev->rx_info;
	unsigned next_rx;
	int rx_rc, len;
	u32 cmdsts;
	__le32 *desc;
	unsigned long flags;
	int nr = 0;

	dprintk("rx_irq(%p)\n", ndev);
	dprintk("rxdp: %08x, descs: %08lx next_rx[%d]: %p next_empty[%d]: %p\n",
		readl(dev->base + RXDP),
		(long)(dev->rx_info.phy_descs),
		(int)dev->rx_info.next_rx,
		(dev->rx_info.descs + (DESC_SIZE * dev->rx_info.next_rx)),
		(int)dev->rx_info.next_empty,
		(dev->rx_info.descs + (DESC_SIZE * dev->rx_info.next_empty))
		);

	spin_lock_irqsave(&info->lock, flags);
	if (!info->up)
		goto out;

	dprintk("walking descs\n");
	next_rx = info->next_rx;
	desc = info->next_rx_desc;
	while ((CMDSTS_OWN & (cmdsts = le32_to_cpu(desc[DESC_CMDSTS]))) &&
	       (cmdsts != CMDSTS_OWN)) {
		struct sk_buff *skb;
		u32 extsts = le32_to_cpu(desc[DESC_EXTSTS]);
		dma_addr_t bufptr = desc_addr_get(desc + DESC_BUFPTR);

		dprintk("cmdsts: %08x\n", cmdsts);
		dprintk("link: %08x\n", cpu_to_le32(desc[DESC_LINK]));
		dprintk("extsts: %08x\n", extsts);

		skb = info->skbs[next_rx];
		info->skbs[next_rx] = NULL;
		info->next_rx = (next_rx + 1) % NR_RX_DESC;

		mb();
		clear_rx_desc(dev, next_rx);

		pci_unmap_single(dev->pci_dev, bufptr,
				 RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
		len = cmdsts & CMDSTS_LEN_MASK;
#ifdef NS83820_VLAN_ACCEL_SUPPORT
		/* NH: As was mentioned below, this chip is kinda
		 * brain dead about vlan tag stripping.  Frames
		 * that are 64 bytes with a vlan header appended
		 * like arp frames, or pings, are flagged as Runts
		 * when the tag is stripped and hardware.  This
		 * also means that the OK bit in the descriptor
		 * is cleared when the frame comes in so we have
		 * to do a specific length check here to make sure
		 * the frame would have been ok, had we not stripped
		 * the tag.
		 */
		if (likely((CMDSTS_OK & cmdsts) ||
			((cmdsts & CMDSTS_RUNT) && len >= 56))) {
#else
		if (likely(CMDSTS_OK & cmdsts)) {
#endif
			skb_put(skb, len);
			if (unlikely(!skb))
				goto netdev_mangle_me_harder_failed;
			if (cmdsts & CMDSTS_DEST_MULTI)
				ndev->stats.multicast++;
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += len;
			if ((extsts & 0x002a0000) && !(extsts & 0x00540000)) {
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			} else {
				skb_checksum_none_assert(skb);
			}
			skb->protocol = eth_type_trans(skb, ndev);
#ifdef NS83820_VLAN_ACCEL_SUPPORT
			if(extsts & EXTSTS_VPKT) {
				unsigned short tag;

				tag = ntohs(extsts & EXTSTS_VTG_MASK);
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_IPV6), tag);
			}
#endif
			rx_rc = netif_rx(skb);
			if (NET_RX_DROP == rx_rc) {
netdev_mangle_me_harder_failed:
				ndev->stats.rx_dropped++;
			}
		} else {
			dev_kfree_skb_irq(skb);
		}

		nr++;
		next_rx = info->next_rx;
		desc = info->descs + (DESC_SIZE * next_rx);
	}
	info->next_rx = next_rx;
	info->next_rx_desc = info->descs + (DESC_SIZE * next_rx);

out:
	if (0 && !nr) {
		Dprintk("dazed: cmdsts_f: %08x\n", cmdsts);
	}

	spin_unlock_irqrestore(&info->lock, flags);
}