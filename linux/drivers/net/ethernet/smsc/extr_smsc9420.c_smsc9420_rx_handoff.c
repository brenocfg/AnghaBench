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
typedef  int u16 ;
struct smsc9420_pdata {scalar_t__ rx_csum; TYPE_2__* rx_buffers; int /*<<< orphan*/  pdev; struct net_device* dev; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_4__ {struct sk_buff* skb; scalar_t__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int const RDES0_FRAME_LENGTH_MASK_ ; 
 int const RDES0_FRAME_LENGTH_SHFT_ ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int get_unaligned_le16 (int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static void smsc9420_rx_handoff(struct smsc9420_pdata *pd, const int index,
				const u32 status)
{
	struct net_device *dev = pd->dev;
	struct sk_buff *skb;
	u16 packet_length = (status & RDES0_FRAME_LENGTH_MASK_)
		>> RDES0_FRAME_LENGTH_SHFT_;

	/* remove crc from packet lendth */
	packet_length -= 4;

	if (pd->rx_csum)
		packet_length -= 2;

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += packet_length;

	pci_unmap_single(pd->pdev, pd->rx_buffers[index].mapping,
		PKT_BUF_SZ, PCI_DMA_FROMDEVICE);
	pd->rx_buffers[index].mapping = 0;

	skb = pd->rx_buffers[index].skb;
	pd->rx_buffers[index].skb = NULL;

	if (pd->rx_csum) {
		u16 hw_csum = get_unaligned_le16(skb_tail_pointer(skb) +
			NET_IP_ALIGN + packet_length + 4);
		put_unaligned_le16(hw_csum, &skb->csum);
		skb->ip_summed = CHECKSUM_COMPLETE;
	}

	skb_reserve(skb, NET_IP_ALIGN);
	skb_put(skb, packet_length);

	skb->protocol = eth_type_trans(skb, dev);

	netif_receive_skb(skb);
}