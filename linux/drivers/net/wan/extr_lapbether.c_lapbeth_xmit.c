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
struct sk_buff {int* data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int LAPB_OK ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
#define  X25_IFACE_CONNECT 130 
#define  X25_IFACE_DATA 129 
#define  X25_IFACE_DISCONNECT 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int lapb_connect_request (struct net_device*) ; 
 int lapb_data_request (struct net_device*,struct sk_buff*) ; 
 int lapb_disconnect_request (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t lapbeth_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	int err;

	/*
	 * Just to be *really* sure not to send anything if the interface
	 * is down, the ethernet device may have gone.
	 */
	if (!netif_running(dev))
		goto drop;

	switch (skb->data[0]) {
	case X25_IFACE_DATA:
		break;
	case X25_IFACE_CONNECT:
		if ((err = lapb_connect_request(dev)) != LAPB_OK)
			pr_err("lapb_connect_request error: %d\n", err);
		goto drop;
	case X25_IFACE_DISCONNECT:
		if ((err = lapb_disconnect_request(dev)) != LAPB_OK)
			pr_err("lapb_disconnect_request err: %d\n", err);
		/* Fall thru */
	default:
		goto drop;
	}

	skb_pull(skb, 1);

	if ((err = lapb_data_request(dev, skb)) != LAPB_OK) {
		pr_err("lapb_data_request error - %d\n", err);
		goto drop;
	}
out:
	return NETDEV_TX_OK;
drop:
	kfree_skb(skb);
	goto out;
}