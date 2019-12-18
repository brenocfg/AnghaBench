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
typedef  int u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int ihl; } ;
struct bnx2_tx_ring_info {size_t tx_prod; struct bnx2_sw_tx_bd* tx_buf_ring; int /*<<< orphan*/  tx_prod_bseq; int /*<<< orphan*/  tx_bseq_addr; int /*<<< orphan*/  tx_bidx_addr; struct bnx2_tx_bd* tx_desc_ring; } ;
struct bnx2_tx_bd {int tx_bd_haddr_hi; int tx_bd_haddr_lo; int tx_bd_mss_nbytes; int tx_bd_vlan_tag_flags; } ;
struct bnx2_sw_tx_bd {int nr_frags; struct sk_buff* skb; int /*<<< orphan*/  is_gso; } ;
struct bnx2_napi {struct bnx2_tx_ring_info tx_ring; } ;
struct bnx2 {scalar_t__ tx_wake_thresh; TYPE_1__* pdev; struct bnx2_napi* bnx2_napi; } ;
typedef  int /*<<< orphan*/  const skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {scalar_t__ nr_frags; int gso_size; int gso_type; int /*<<< orphan*/  const* frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BNX2_NEXT_TX_BD (size_t) ; 
 size_t BNX2_TX_RING_IDX (size_t) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR16 (struct bnx2*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ETH_HLEN ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int SKB_GSO_TCPV6 ; 
 int TX_BD_FLAGS_END ; 
 int TX_BD_FLAGS_START ; 
 int TX_BD_FLAGS_SW_FLAGS ; 
 int TX_BD_FLAGS_SW_LSO ; 
 int TX_BD_FLAGS_TCP6_OFF0_MSK ; 
 int TX_BD_FLAGS_TCP6_OFF0_SHL ; 
 int TX_BD_FLAGS_TCP6_OFF4_SHL ; 
 int TX_BD_FLAGS_TCP_UDP_CKSUM ; 
 int TX_BD_FLAGS_VLAN_TAG ; 
 int TX_BD_TCP6_OFF2_SHL ; 
 scalar_t__ bnx2_tx_avail (struct bnx2*,struct bnx2_tx_ring_info*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnx2_sw_tx_bd*,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bnx2_sw_tx_bd*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int tcp_optlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t
bnx2_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bnx2 *bp = netdev_priv(dev);
	dma_addr_t mapping;
	struct bnx2_tx_bd *txbd;
	struct bnx2_sw_tx_bd *tx_buf;
	u32 len, vlan_tag_flags, last_frag, mss;
	u16 prod, ring_prod;
	int i;
	struct bnx2_napi *bnapi;
	struct bnx2_tx_ring_info *txr;
	struct netdev_queue *txq;

	/*  Determine which tx ring we will be placed on */
	i = skb_get_queue_mapping(skb);
	bnapi = &bp->bnx2_napi[i];
	txr = &bnapi->tx_ring;
	txq = netdev_get_tx_queue(dev, i);

	if (unlikely(bnx2_tx_avail(bp, txr) <
	    (skb_shinfo(skb)->nr_frags + 1))) {
		netif_tx_stop_queue(txq);
		netdev_err(dev, "BUG! Tx ring full when queue awake!\n");

		return NETDEV_TX_BUSY;
	}
	len = skb_headlen(skb);
	prod = txr->tx_prod;
	ring_prod = BNX2_TX_RING_IDX(prod);

	vlan_tag_flags = 0;
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		vlan_tag_flags |= TX_BD_FLAGS_TCP_UDP_CKSUM;
	}

	if (skb_vlan_tag_present(skb)) {
		vlan_tag_flags |=
			(TX_BD_FLAGS_VLAN_TAG | (skb_vlan_tag_get(skb) << 16));
	}

	if ((mss = skb_shinfo(skb)->gso_size)) {
		u32 tcp_opt_len;
		struct iphdr *iph;

		vlan_tag_flags |= TX_BD_FLAGS_SW_LSO;

		tcp_opt_len = tcp_optlen(skb);

		if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) {
			u32 tcp_off = skb_transport_offset(skb) -
				      sizeof(struct ipv6hdr) - ETH_HLEN;

			vlan_tag_flags |= ((tcp_opt_len >> 2) << 8) |
					  TX_BD_FLAGS_SW_FLAGS;
			if (likely(tcp_off == 0))
				vlan_tag_flags &= ~TX_BD_FLAGS_TCP6_OFF0_MSK;
			else {
				tcp_off >>= 3;
				vlan_tag_flags |= ((tcp_off & 0x3) <<
						   TX_BD_FLAGS_TCP6_OFF0_SHL) |
						  ((tcp_off & 0x10) <<
						   TX_BD_FLAGS_TCP6_OFF4_SHL);
				mss |= (tcp_off & 0xc) << TX_BD_TCP6_OFF2_SHL;
			}
		} else {
			iph = ip_hdr(skb);
			if (tcp_opt_len || (iph->ihl > 5)) {
				vlan_tag_flags |= ((iph->ihl - 5) +
						   (tcp_opt_len >> 2)) << 8;
			}
		}
	} else
		mss = 0;

	mapping = dma_map_single(&bp->pdev->dev, skb->data, len, PCI_DMA_TODEVICE);
	if (dma_mapping_error(&bp->pdev->dev, mapping)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	tx_buf = &txr->tx_buf_ring[ring_prod];
	tx_buf->skb = skb;
	dma_unmap_addr_set(tx_buf, mapping, mapping);

	txbd = &txr->tx_desc_ring[ring_prod];

	txbd->tx_bd_haddr_hi = (u64) mapping >> 32;
	txbd->tx_bd_haddr_lo = (u64) mapping & 0xffffffff;
	txbd->tx_bd_mss_nbytes = len | (mss << 16);
	txbd->tx_bd_vlan_tag_flags = vlan_tag_flags | TX_BD_FLAGS_START;

	last_frag = skb_shinfo(skb)->nr_frags;
	tx_buf->nr_frags = last_frag;
	tx_buf->is_gso = skb_is_gso(skb);

	for (i = 0; i < last_frag; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		prod = BNX2_NEXT_TX_BD(prod);
		ring_prod = BNX2_TX_RING_IDX(prod);
		txbd = &txr->tx_desc_ring[ring_prod];

		len = skb_frag_size(frag);
		mapping = skb_frag_dma_map(&bp->pdev->dev, frag, 0, len,
					   DMA_TO_DEVICE);
		if (dma_mapping_error(&bp->pdev->dev, mapping))
			goto dma_error;
		dma_unmap_addr_set(&txr->tx_buf_ring[ring_prod], mapping,
				   mapping);

		txbd->tx_bd_haddr_hi = (u64) mapping >> 32;
		txbd->tx_bd_haddr_lo = (u64) mapping & 0xffffffff;
		txbd->tx_bd_mss_nbytes = len | (mss << 16);
		txbd->tx_bd_vlan_tag_flags = vlan_tag_flags;

	}
	txbd->tx_bd_vlan_tag_flags |= TX_BD_FLAGS_END;

	/* Sync BD data before updating TX mailbox */
	wmb();

	netdev_tx_sent_queue(txq, skb->len);

	prod = BNX2_NEXT_TX_BD(prod);
	txr->tx_prod_bseq += skb->len;

	BNX2_WR16(bp, txr->tx_bidx_addr, prod);
	BNX2_WR(bp, txr->tx_bseq_addr, txr->tx_prod_bseq);

	txr->tx_prod = prod;

	if (unlikely(bnx2_tx_avail(bp, txr) <= MAX_SKB_FRAGS)) {
		netif_tx_stop_queue(txq);

		/* netif_tx_stop_queue() must be done before checking
		 * tx index in bnx2_tx_avail() below, because in
		 * bnx2_tx_int(), we update tx index before checking for
		 * netif_tx_queue_stopped().
		 */
		smp_mb();
		if (bnx2_tx_avail(bp, txr) > bp->tx_wake_thresh)
			netif_tx_wake_queue(txq);
	}

	return NETDEV_TX_OK;
dma_error:
	/* save value of frag that failed */
	last_frag = i;

	/* start back at beginning and unmap skb */
	prod = txr->tx_prod;
	ring_prod = BNX2_TX_RING_IDX(prod);
	tx_buf = &txr->tx_buf_ring[ring_prod];
	tx_buf->skb = NULL;
	dma_unmap_single(&bp->pdev->dev, dma_unmap_addr(tx_buf, mapping),
			 skb_headlen(skb), PCI_DMA_TODEVICE);

	/* unmap remaining mapped pages */
	for (i = 0; i < last_frag; i++) {
		prod = BNX2_NEXT_TX_BD(prod);
		ring_prod = BNX2_TX_RING_IDX(prod);
		tx_buf = &txr->tx_buf_ring[ring_prod];
		dma_unmap_page(&bp->pdev->dev, dma_unmap_addr(tx_buf, mapping),
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       PCI_DMA_TODEVICE);
	}

	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}