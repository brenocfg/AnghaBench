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
typedef  int u32 ;
struct sk_buff {unsigned int tail; unsigned int len; scalar_t__ pkt_type; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {unsigned int bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  packets; } ;
struct rtl8169_private {unsigned int cur_rx; TYPE_2__ rx_stats; int /*<<< orphan*/  napi; struct RxDesc* RxDescArray; int /*<<< orphan*/ * Rx_databuff; } ;
struct TYPE_3__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int features; TYPE_1__ stats; } ;
struct RxDesc {scalar_t__ opts2; int /*<<< orphan*/  addr; int /*<<< orphan*/  opts1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DescOwn ; 
 scalar_t__ ETH_FCS_LEN ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 unsigned int NUM_RX_DESC ; 
 scalar_t__ PACKET_MULTICAST ; 
 int RxCRC ; 
 int RxRES ; 
 int RxRUNT ; 
 int RxRWT ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (int,unsigned int) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_info (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (void const*) ; 
 int rtl8169_fragmented_frame (int) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (struct RxDesc*) ; 
 int /*<<< orphan*/  rtl8169_rx_csum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rtl8169_rx_vlan_tag (struct RxDesc*,struct sk_buff*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void const*,unsigned int) ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rtl_rx(struct net_device *dev, struct rtl8169_private *tp, u32 budget)
{
	unsigned int cur_rx, rx_left;
	unsigned int count;

	cur_rx = tp->cur_rx;

	for (rx_left = min(budget, NUM_RX_DESC); rx_left > 0; rx_left--, cur_rx++) {
		unsigned int entry = cur_rx % NUM_RX_DESC;
		const void *rx_buf = page_address(tp->Rx_databuff[entry]);
		struct RxDesc *desc = tp->RxDescArray + entry;
		u32 status;

		status = le32_to_cpu(desc->opts1);
		if (status & DescOwn)
			break;

		/* This barrier is needed to keep us from reading
		 * any other fields out of the Rx descriptor until
		 * we know the status of DescOwn
		 */
		dma_rmb();

		if (unlikely(status & RxRES)) {
			netif_info(tp, rx_err, dev, "Rx ERROR. status = %08x\n",
				   status);
			dev->stats.rx_errors++;
			if (status & (RxRWT | RxRUNT))
				dev->stats.rx_length_errors++;
			if (status & RxCRC)
				dev->stats.rx_crc_errors++;
			if (status & (RxRUNT | RxCRC) && !(status & RxRWT) &&
			    dev->features & NETIF_F_RXALL) {
				goto process_pkt;
			}
		} else {
			unsigned int pkt_size;
			struct sk_buff *skb;

process_pkt:
			pkt_size = status & GENMASK(13, 0);
			if (likely(!(dev->features & NETIF_F_RXFCS)))
				pkt_size -= ETH_FCS_LEN;
			/*
			 * The driver does not support incoming fragmented
			 * frames. They are seen as a symptom of over-mtu
			 * sized frames.
			 */
			if (unlikely(rtl8169_fragmented_frame(status))) {
				dev->stats.rx_dropped++;
				dev->stats.rx_length_errors++;
				goto release_descriptor;
			}

			skb = napi_alloc_skb(&tp->napi, pkt_size);
			if (unlikely(!skb)) {
				dev->stats.rx_dropped++;
				goto release_descriptor;
			}

			dma_sync_single_for_cpu(tp_to_dev(tp),
						le64_to_cpu(desc->addr),
						pkt_size, DMA_FROM_DEVICE);
			prefetch(rx_buf);
			skb_copy_to_linear_data(skb, rx_buf, pkt_size);
			skb->tail += pkt_size;
			skb->len = pkt_size;

			dma_sync_single_for_device(tp_to_dev(tp),
						   le64_to_cpu(desc->addr),
						   pkt_size, DMA_FROM_DEVICE);

			rtl8169_rx_csum(skb, status);
			skb->protocol = eth_type_trans(skb, dev);

			rtl8169_rx_vlan_tag(desc, skb);

			if (skb->pkt_type == PACKET_MULTICAST)
				dev->stats.multicast++;

			napi_gro_receive(&tp->napi, skb);

			u64_stats_update_begin(&tp->rx_stats.syncp);
			tp->rx_stats.packets++;
			tp->rx_stats.bytes += pkt_size;
			u64_stats_update_end(&tp->rx_stats.syncp);
		}
release_descriptor:
		desc->opts2 = 0;
		rtl8169_mark_to_asic(desc);
	}

	count = cur_rx - tp->cur_rx;
	tp->cur_rx = cur_rx;

	return count;
}