#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {unsigned int len; int /*<<< orphan*/ * data; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  hex_dump_to_buffer (int /*<<< orphan*/ *,unsigned int,int,int,unsigned char*,int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void xgbe_print_pkt(struct net_device *netdev, struct sk_buff *skb, bool tx_rx)
{
	struct ethhdr *eth = (struct ethhdr *)skb->data;
	unsigned char buffer[128];
	unsigned int i;

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");

	netdev_dbg(netdev, "%s packet of %d bytes\n",
		   (tx_rx ? "TX" : "RX"), skb->len);

	netdev_dbg(netdev, "Dst MAC addr: %pM\n", eth->h_dest);
	netdev_dbg(netdev, "Src MAC addr: %pM\n", eth->h_source);
	netdev_dbg(netdev, "Protocol: %#06hx\n", ntohs(eth->h_proto));

	for (i = 0; i < skb->len; i += 32) {
		unsigned int len = min(skb->len - i, 32U);

		hex_dump_to_buffer(&skb->data[i], len, 32, 1,
				   buffer, sizeof(buffer), false);
		netdev_dbg(netdev, "  %#06x: %s\n", i, buffer);
	}

	netdev_dbg(netdev, "\n************** SKB dump ****************\n");
}