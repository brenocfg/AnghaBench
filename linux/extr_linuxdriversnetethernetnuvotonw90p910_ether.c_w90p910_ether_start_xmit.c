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
struct w90p910_ether {struct sk_buff* skb; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_send_frame (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w90p910_ether_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);

	if (!(w90p910_send_frame(dev, skb->data, skb->len))) {
		ether->skb = skb;
		dev_kfree_skb_irq(skb);
		return 0;
	}
	return -EAGAIN;
}