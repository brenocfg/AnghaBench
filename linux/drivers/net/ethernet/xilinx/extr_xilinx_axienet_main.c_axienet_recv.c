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
struct sk_buff {scalar_t__ protocol; int len; int /*<<< orphan*/  data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ stats; TYPE_1__ dev; } ;
struct axienet_local {size_t rx_bd_ci; int features; int rx_bd_num; struct axidma_bd* rx_bd_v; int /*<<< orphan*/  max_frm_size; scalar_t__ rx_bd_p; } ;
struct axidma_bd {int status; int app4; int app2; int app3; struct sk_buff* skb; int /*<<< orphan*/  cntrl; int /*<<< orphan*/  phys; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int XAE_FEATURE_FULL_RX_CSUM ; 
 int XAE_FEATURE_PARTIAL_RX_CSUM ; 
 int XAE_FULL_CSUM_STATUS_MASK ; 
 int XAE_IP_TCP_CSUM_VALIDATED ; 
 int XAE_IP_UDP_CSUM_VALIDATED ; 
 int XAXIDMA_BD_STS_COMPLETE_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_TDESC_OFFSET ; 
 int /*<<< orphan*/  axienet_dma_out32 (struct axienet_local*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void axienet_recv(struct net_device *ndev)
{
	u32 length;
	u32 csumstatus;
	u32 size = 0;
	u32 packets = 0;
	dma_addr_t tail_p = 0;
	struct axienet_local *lp = netdev_priv(ndev);
	struct sk_buff *skb, *new_skb;
	struct axidma_bd *cur_p;

	cur_p = &lp->rx_bd_v[lp->rx_bd_ci];

	while ((cur_p->status & XAXIDMA_BD_STS_COMPLETE_MASK)) {
		tail_p = lp->rx_bd_p + sizeof(*lp->rx_bd_v) * lp->rx_bd_ci;

		dma_unmap_single(ndev->dev.parent, cur_p->phys,
				 lp->max_frm_size,
				 DMA_FROM_DEVICE);

		skb = cur_p->skb;
		cur_p->skb = NULL;
		length = cur_p->app4 & 0x0000FFFF;

		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, ndev);
		/*skb_checksum_none_assert(skb);*/
		skb->ip_summed = CHECKSUM_NONE;

		/* if we're doing Rx csum offload, set it up */
		if (lp->features & XAE_FEATURE_FULL_RX_CSUM) {
			csumstatus = (cur_p->app2 &
				      XAE_FULL_CSUM_STATUS_MASK) >> 3;
			if ((csumstatus == XAE_IP_TCP_CSUM_VALIDATED) ||
			    (csumstatus == XAE_IP_UDP_CSUM_VALIDATED)) {
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			}
		} else if ((lp->features & XAE_FEATURE_PARTIAL_RX_CSUM) != 0 &&
			   skb->protocol == htons(ETH_P_IP) &&
			   skb->len > 64) {
			skb->csum = be32_to_cpu(cur_p->app3 & 0xFFFF);
			skb->ip_summed = CHECKSUM_COMPLETE;
		}

		netif_rx(skb);

		size += length;
		packets++;

		new_skb = netdev_alloc_skb_ip_align(ndev, lp->max_frm_size);
		if (!new_skb)
			return;

		cur_p->phys = dma_map_single(ndev->dev.parent, new_skb->data,
					     lp->max_frm_size,
					     DMA_FROM_DEVICE);
		cur_p->cntrl = lp->max_frm_size;
		cur_p->status = 0;
		cur_p->skb = new_skb;

		if (++lp->rx_bd_ci >= lp->rx_bd_num)
			lp->rx_bd_ci = 0;
		cur_p = &lp->rx_bd_v[lp->rx_bd_ci];
	}

	ndev->stats.rx_packets += packets;
	ndev->stats.rx_bytes += size;

	if (tail_p)
		axienet_dma_out32(lp, XAXIDMA_RX_TDESC_OFFSET, tail_p);
}