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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned char X25_IFACE_CONNECT ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct x25_asy* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x25_asy_connected(struct net_device *dev, int reason)
{
	struct x25_asy *sl = netdev_priv(dev);
	struct sk_buff *skb;
	unsigned char *ptr;

	skb = dev_alloc_skb(1);
	if (skb == NULL) {
		netdev_err(dev, "out of memory\n");
		return;
	}

	ptr  = skb_put(skb, 1);
	*ptr = X25_IFACE_CONNECT;

	skb->protocol = x25_type_trans(skb, sl->dev);
	netif_rx(skb);
}