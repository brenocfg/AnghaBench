#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {scalar_t__ ip_summed; int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct iphdr {scalar_t__ protocol; } ;
struct cp_private {unsigned int tx_head; int* tx_opts; TYPE_4__* dev; int /*<<< orphan*/  lock; struct cp_desc* tx_ring; struct sk_buff** tx_skb; TYPE_2__* pdev; } ;
struct cp_desc {void* opts1; void* addr; void* opts2; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  void* __le32 ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_8__ {TYPE_1__ stats; } ;
struct TYPE_7__ {int nr_frags; int gso_size; int /*<<< orphan*/ * frags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CP_TX_RING_SIZE ; 
 int DescOwn ; 
 int FirstFrag ; 
 int IPCS ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int LargeSend ; 
 int LastFrag ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int MSSMask ; 
 int MSSShift ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 void* NEXT_TX (unsigned int) ; 
 int /*<<< orphan*/  NormalTxPoll ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int RingEnd ; 
 int TCPCS ; 
 scalar_t__ TX_BUFFS_AVAIL (struct cp_private*) ; 
 int /*<<< orphan*/  TxPoll ; 
 int UDPCS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int cp_tx_vlan_tag (struct sk_buff*) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_WARN_ONCE (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct cp_private*,int /*<<< orphan*/ ,TYPE_4__*,char*,int,unsigned int,...) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/  const*) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_queued ; 
 int /*<<< orphan*/  unwind_tx_frag_mapping (struct cp_private*,struct sk_buff*,int,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t cp_start_xmit (struct sk_buff *skb,
					struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned entry;
	u32 eor, opts1;
	unsigned long intr_flags;
	__le32 opts2;
	int mss = 0;

	spin_lock_irqsave(&cp->lock, intr_flags);

	/* This is a hard error, log it. */
	if (TX_BUFFS_AVAIL(cp) <= (skb_shinfo(skb)->nr_frags + 1)) {
		netif_stop_queue(dev);
		spin_unlock_irqrestore(&cp->lock, intr_flags);
		netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		return NETDEV_TX_BUSY;
	}

	entry = cp->tx_head;
	eor = (entry == (CP_TX_RING_SIZE - 1)) ? RingEnd : 0;
	mss = skb_shinfo(skb)->gso_size;

	if (mss > MSSMask) {
		netdev_WARN_ONCE(dev, "Net bug: GSO size %d too large for 8139CP\n",
				 mss);
		goto out_dma_error;
	}

	opts2 = cpu_to_le32(cp_tx_vlan_tag(skb));
	opts1 = DescOwn;
	if (mss)
		opts1 |= LargeSend | (mss << MSSShift);
	else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		const struct iphdr *ip = ip_hdr(skb);
		if (ip->protocol == IPPROTO_TCP)
			opts1 |= IPCS | TCPCS;
		else if (ip->protocol == IPPROTO_UDP)
			opts1 |= IPCS | UDPCS;
		else {
			WARN_ONCE(1,
				  "Net bug: asked to checksum invalid Legacy IP packet\n");
			goto out_dma_error;
		}
	}

	if (skb_shinfo(skb)->nr_frags == 0) {
		struct cp_desc *txd = &cp->tx_ring[entry];
		u32 len;
		dma_addr_t mapping;

		len = skb->len;
		mapping = dma_map_single(&cp->pdev->dev, skb->data, len, PCI_DMA_TODEVICE);
		if (dma_mapping_error(&cp->pdev->dev, mapping))
			goto out_dma_error;

		txd->opts2 = opts2;
		txd->addr = cpu_to_le64(mapping);
		wmb();

		opts1 |= eor | len | FirstFrag | LastFrag;

		txd->opts1 = cpu_to_le32(opts1);
		wmb();

		cp->tx_skb[entry] = skb;
		cp->tx_opts[entry] = opts1;
		netif_dbg(cp, tx_queued, cp->dev, "tx queued, slot %d, skblen %d\n",
			  entry, skb->len);
	} else {
		struct cp_desc *txd;
		u32 first_len, first_eor, ctrl;
		dma_addr_t first_mapping;
		int frag, first_entry = entry;

		/* We must give this initial chunk to the device last.
		 * Otherwise we could race with the device.
		 */
		first_eor = eor;
		first_len = skb_headlen(skb);
		first_mapping = dma_map_single(&cp->pdev->dev, skb->data,
					       first_len, PCI_DMA_TODEVICE);
		if (dma_mapping_error(&cp->pdev->dev, first_mapping))
			goto out_dma_error;

		cp->tx_skb[entry] = skb;

		for (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) {
			const skb_frag_t *this_frag = &skb_shinfo(skb)->frags[frag];
			u32 len;
			dma_addr_t mapping;

			entry = NEXT_TX(entry);

			len = skb_frag_size(this_frag);
			mapping = dma_map_single(&cp->pdev->dev,
						 skb_frag_address(this_frag),
						 len, PCI_DMA_TODEVICE);
			if (dma_mapping_error(&cp->pdev->dev, mapping)) {
				unwind_tx_frag_mapping(cp, skb, first_entry, entry);
				goto out_dma_error;
			}

			eor = (entry == (CP_TX_RING_SIZE - 1)) ? RingEnd : 0;

			ctrl = opts1 | eor | len;

			if (frag == skb_shinfo(skb)->nr_frags - 1)
				ctrl |= LastFrag;

			txd = &cp->tx_ring[entry];
			txd->opts2 = opts2;
			txd->addr = cpu_to_le64(mapping);
			wmb();

			txd->opts1 = cpu_to_le32(ctrl);
			wmb();

			cp->tx_opts[entry] = ctrl;
			cp->tx_skb[entry] = skb;
		}

		txd = &cp->tx_ring[first_entry];
		txd->opts2 = opts2;
		txd->addr = cpu_to_le64(first_mapping);
		wmb();

		ctrl = opts1 | first_eor | first_len | FirstFrag;
		txd->opts1 = cpu_to_le32(ctrl);
		wmb();

		cp->tx_opts[first_entry] = ctrl;
		netif_dbg(cp, tx_queued, cp->dev, "tx queued, slots %d-%d, skblen %d\n",
			  first_entry, entry, skb->len);
	}
	cp->tx_head = NEXT_TX(entry);

	netdev_sent_queue(dev, skb->len);
	if (TX_BUFFS_AVAIL(cp) <= (MAX_SKB_FRAGS + 1))
		netif_stop_queue(dev);

out_unlock:
	spin_unlock_irqrestore(&cp->lock, intr_flags);

	cpw8(TxPoll, NormalTxPoll);

	return NETDEV_TX_OK;
out_dma_error:
	dev_kfree_skb_any(skb);
	cp->dev->stats.tx_dropped++;
	goto out_unlock;
}