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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {int features; TYPE_1__ stats; } ;
struct napi_struct {int dummy; } ;
struct mtk_rx_ring {int calc_idx; int /*<<< orphan*/  buf_size; int /*<<< orphan*/ ** data; int /*<<< orphan*/  frag_size; struct mtk_rx_dma* dma; int /*<<< orphan*/  dma_size; } ;
struct mtk_rx_dma {int rxd2; int rxd4; unsigned int rxd1; int /*<<< orphan*/  rxd3; } ;
struct mtk_eth {int ip_align; int rx_dma_l4_valid; TYPE_2__* soc; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; struct net_device** netdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MTK_MAC_COUNT ; 
 int /*<<< orphan*/  MTK_RESETTING ; 
 int /*<<< orphan*/  MTK_SOC_MT7628 ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 int NEXT_DESP_IDX (int,int /*<<< orphan*/ ) ; 
 int RX_DMA_DONE ; 
 int RX_DMA_FPORT_MASK ; 
 int RX_DMA_FPORT_SHIFT ; 
 unsigned int RX_DMA_GET_PLEN0 (int) ; 
 int RX_DMA_LSO ; 
 int RX_DMA_PLEN0 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_DMA_VID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct mtk_rx_ring* mtk_get_rx_ring (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_rx_get_desc (struct mtk_rx_dma*,struct mtk_rx_dma*) ; 
 int /*<<< orphan*/  mtk_update_rx_cpu_idx (struct mtk_eth*) ; 
 int /*<<< orphan*/ * napi_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_poll_rx(struct napi_struct *napi, int budget,
		       struct mtk_eth *eth)
{
	struct mtk_rx_ring *ring;
	int idx;
	struct sk_buff *skb;
	u8 *data, *new_data;
	struct mtk_rx_dma *rxd, trxd;
	int done = 0;

	while (done < budget) {
		struct net_device *netdev;
		unsigned int pktlen;
		dma_addr_t dma_addr;
		int mac;

		ring = mtk_get_rx_ring(eth);
		if (unlikely(!ring))
			goto rx_done;

		idx = NEXT_DESP_IDX(ring->calc_idx, ring->dma_size);
		rxd = &ring->dma[idx];
		data = ring->data[idx];

		mtk_rx_get_desc(&trxd, rxd);
		if (!(trxd.rxd2 & RX_DMA_DONE))
			break;

		/* find out which mac the packet come from. values start at 1 */
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
			mac = 0;
		} else {
			mac = (trxd.rxd4 >> RX_DMA_FPORT_SHIFT) &
				RX_DMA_FPORT_MASK;
			mac--;
		}

		if (unlikely(mac < 0 || mac >= MTK_MAC_COUNT ||
			     !eth->netdev[mac]))
			goto release_desc;

		netdev = eth->netdev[mac];

		if (unlikely(test_bit(MTK_RESETTING, &eth->state)))
			goto release_desc;

		/* alloc new buffer */
		new_data = napi_alloc_frag(ring->frag_size);
		if (unlikely(!new_data)) {
			netdev->stats.rx_dropped++;
			goto release_desc;
		}
		dma_addr = dma_map_single(eth->dev,
					  new_data + NET_SKB_PAD +
					  eth->ip_align,
					  ring->buf_size,
					  DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(eth->dev, dma_addr))) {
			skb_free_frag(new_data);
			netdev->stats.rx_dropped++;
			goto release_desc;
		}

		/* receive data */
		skb = build_skb(data, ring->frag_size);
		if (unlikely(!skb)) {
			skb_free_frag(new_data);
			netdev->stats.rx_dropped++;
			goto release_desc;
		}
		skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);

		dma_unmap_single(eth->dev, trxd.rxd1,
				 ring->buf_size, DMA_FROM_DEVICE);
		pktlen = RX_DMA_GET_PLEN0(trxd.rxd2);
		skb->dev = netdev;
		skb_put(skb, pktlen);
		if (trxd.rxd4 & eth->rx_dma_l4_valid)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		else
			skb_checksum_none_assert(skb);
		skb->protocol = eth_type_trans(skb, netdev);

		if (netdev->features & NETIF_F_HW_VLAN_CTAG_RX &&
		    RX_DMA_VID(trxd.rxd3))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       RX_DMA_VID(trxd.rxd3));
		skb_record_rx_queue(skb, 0);
		napi_gro_receive(napi, skb);

		ring->data[idx] = new_data;
		rxd->rxd1 = (unsigned int)dma_addr;

release_desc:
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			rxd->rxd2 = RX_DMA_LSO;
		else
			rxd->rxd2 = RX_DMA_PLEN0(ring->buf_size);

		ring->calc_idx = idx;

		done++;
	}

rx_done:
	if (done) {
		/* make sure that all changes to the dma ring are flushed before
		 * we continue
		 */
		wmb();
		mtk_update_rx_cpu_idx(eth);
	}

	return done;
}