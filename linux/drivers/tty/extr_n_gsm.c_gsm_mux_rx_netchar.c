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
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct gsm_mux_net {int dummy; } ;
struct gsm_dlci {struct net_device* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ NET_IP_ALIGN ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muxnet_get (struct gsm_mux_net*) ; 
 int /*<<< orphan*/  muxnet_put (struct gsm_mux_net*) ; 
 struct gsm_mux_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char const*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void gsm_mux_rx_netchar(struct gsm_dlci *dlci,
				const unsigned char *in_buf, int size)
{
	struct net_device *net = dlci->net;
	struct sk_buff *skb;
	struct gsm_mux_net *mux_net = netdev_priv(net);
	muxnet_get(mux_net);

	/* Allocate an sk_buff */
	skb = dev_alloc_skb(size + NET_IP_ALIGN);
	if (!skb) {
		/* We got no receive buffer. */
		net->stats.rx_dropped++;
		muxnet_put(mux_net);
		return;
	}
	skb_reserve(skb, NET_IP_ALIGN);
	skb_put_data(skb, in_buf, size);

	skb->dev = net;
	skb->protocol = htons(ETH_P_IP);

	/* Ship it off to the kernel */
	netif_rx(skb);

	/* update out statistics */
	net->stats.rx_packets++;
	net->stats.rx_bytes += size;
	muxnet_put(mux_net);
	return;
}