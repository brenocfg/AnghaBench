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
struct xircom_private {int /*<<< orphan*/ * rx_buffer; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {short rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,short) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,short) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trigger_receive (struct xircom_private*) ; 

__attribute__((used)) static void
investigate_read_descriptor(struct net_device *dev, struct xircom_private *card,
			    int descnr, unsigned int bufferoffset)
{
	int status;

	status = le32_to_cpu(card->rx_buffer[4*descnr]);

	if (status > 0) {		/* packet received */

		/* TODO: discard error packets */

		short pkt_len = ((status >> 16) & 0x7ff) - 4;
					/* minus 4, we don't want the CRC */
		struct sk_buff *skb;

		if (pkt_len > 1518) {
			netdev_err(dev, "Packet length %i is bogus\n", pkt_len);
			pkt_len = 1518;
		}

		skb = netdev_alloc_skb(dev, pkt_len + 2);
		if (skb == NULL) {
			dev->stats.rx_dropped++;
			goto out;
		}
		skb_reserve(skb, 2);
		skb_copy_to_linear_data(skb,
					&card->rx_buffer[bufferoffset / 4],
					pkt_len);
		skb_put(skb, pkt_len);
		skb->protocol = eth_type_trans(skb, dev);
		netif_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pkt_len;

out:
		/* give the buffer back to the card */
		card->rx_buffer[4*descnr] = cpu_to_le32(0x80000000);
		trigger_receive(card);
	}
}