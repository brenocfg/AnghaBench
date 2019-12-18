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
struct sk_buff {int dummy; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
struct hdlc_device {TYPE_1__* proto; } ;
struct TYPE_2__ {int (* netif_rx ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct hdlc_device* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static int hdlc_rcv(struct sk_buff *skb, struct net_device *dev,
		    struct packet_type *p, struct net_device *orig_dev)
{
	struct hdlc_device *hdlc = dev_to_hdlc(dev);

	if (!net_eq(dev_net(dev), &init_net)) {
		kfree_skb(skb);
		return 0;
	}

	BUG_ON(!hdlc->proto->netif_rx);
	return hdlc->proto->netif_rx(skb);
}