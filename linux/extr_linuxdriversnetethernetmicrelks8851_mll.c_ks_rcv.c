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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct type_frame_head {int sts; int len; } ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ks_net {int frame_cnt; int rc_rxqcr; struct type_frame_head* frame_head_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_RXFCTR ; 
 int /*<<< orphan*/  KS_RXFHBCR ; 
 int /*<<< orphan*/  KS_RXFHSR ; 
 int /*<<< orphan*/  KS_RXQCR ; 
 int RXFSHR_RXFV ; 
 int RXQCR_RRXEF ; 
 int RX_BUF_SIZE ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_read_qmu (struct ks_net*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ks_rcv(struct ks_net *ks, struct net_device *netdev)
{
	u32	i;
	struct type_frame_head *frame_hdr = ks->frame_head_info;
	struct sk_buff *skb;

	ks->frame_cnt = ks_rdreg16(ks, KS_RXFCTR) >> 8;

	/* read all header information */
	for (i = 0; i < ks->frame_cnt; i++) {
		/* Checking Received packet status */
		frame_hdr->sts = ks_rdreg16(ks, KS_RXFHSR);
		/* Get packet len from hardware */
		frame_hdr->len = ks_rdreg16(ks, KS_RXFHBCR);
		frame_hdr++;
	}

	frame_hdr = ks->frame_head_info;
	while (ks->frame_cnt--) {
		if (unlikely(!(frame_hdr->sts & RXFSHR_RXFV) ||
			     frame_hdr->len >= RX_BUF_SIZE ||
			     frame_hdr->len <= 0)) {

			/* discard an invalid packet */
			ks_wrreg16(ks, KS_RXQCR, (ks->rc_rxqcr | RXQCR_RRXEF));
			netdev->stats.rx_dropped++;
			if (!(frame_hdr->sts & RXFSHR_RXFV))
				netdev->stats.rx_frame_errors++;
			else
				netdev->stats.rx_length_errors++;
			frame_hdr++;
			continue;
		}

		skb = netdev_alloc_skb(netdev, frame_hdr->len + 16);
		if (likely(skb)) {
			skb_reserve(skb, 2);
			/* read data block including CRC 4 bytes */
			ks_read_qmu(ks, (u16 *)skb->data, frame_hdr->len);
			skb_put(skb, frame_hdr->len - 4);
			skb->protocol = eth_type_trans(skb, netdev);
			netif_rx(skb);
			/* exclude CRC size */
			netdev->stats.rx_bytes += frame_hdr->len - 4;
			netdev->stats.rx_packets++;
		} else {
			ks_wrreg16(ks, KS_RXQCR, (ks->rc_rxqcr | RXQCR_RRXEF));
			netdev->stats.rx_dropped++;
		}
		frame_hdr++;
	}
}