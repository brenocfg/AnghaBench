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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int nf_hook (int /*<<< orphan*/ ,unsigned int,struct net*,int /*<<< orphan*/ *,struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrf_rcv_finish ; 

__attribute__((used)) static struct sk_buff *vrf_rcv_nfhook(u8 pf, unsigned int hook,
				      struct sk_buff *skb,
				      struct net_device *dev)
{
	struct net *net = dev_net(dev);

	if (nf_hook(pf, hook, net, NULL, skb, dev, NULL, vrf_rcv_finish) != 1)
		skb = NULL;    /* kfree_skb(skb) handled by nf code */

	return skb;
}