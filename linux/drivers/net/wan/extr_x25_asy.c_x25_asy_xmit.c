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
struct x25_asy {int /*<<< orphan*/  dev; } ;
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
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t x25_asy_xmit(struct sk_buff *skb,
				      struct net_device *dev)
{
	struct x25_asy *sl = netdev_priv(dev);
	int err;

	if (!netif_running(sl->dev)) {
		netdev_err(dev, "xmit call when iface is down\n");
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	switch (skb->data[0]) {
	case X25_IFACE_DATA:
		break;
	case X25_IFACE_CONNECT: /* Connection request .. do nothing */
		err = lapb_connect_request(dev);
		if (err != LAPB_OK)
			netdev_err(dev, "lapb_connect_request error: %d\n",
				   err);
		kfree_skb(skb);
		return NETDEV_TX_OK;
	case X25_IFACE_DISCONNECT: /* do nothing - hang up ?? */
		err = lapb_disconnect_request(dev);
		if (err != LAPB_OK)
			netdev_err(dev, "lapb_disconnect_request error: %d\n",
				   err);
		/* fall through */
	default:
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	skb_pull(skb, 1);	/* Remove control byte */
	/*
	 * If we are busy already- too bad.  We ought to be able
	 * to queue things at this point, to allow for a little
	 * frame buffer.  Oh well...
	 * -----------------------------------------------------
	 * I hate queues in X.25 driver. May be it's efficient,
	 * but for me latency is more important. ;)
	 * So, no queues !
	 *        14 Oct 1994  Dmitry Gorodchanin.
	 */

	err = lapb_data_request(dev, skb);
	if (err != LAPB_OK) {
		netdev_err(dev, "lapb_data_request error: %d\n", err);
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	return NETDEV_TX_OK;
}