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
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 struct net* dev_net (struct net_device*) ; 
 scalar_t__ likely (int) ; 
 int nf_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,struct net_device*,int (*) (struct net*,struct sock*,struct sk_buff*)) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int vrf_output_direct (struct net*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *vrf_ip_out_direct(struct net_device *vrf_dev,
					 struct sock *sk,
					 struct sk_buff *skb)
{
	struct net *net = dev_net(vrf_dev);
	int err;

	skb->dev = vrf_dev;

	err = nf_hook(NFPROTO_IPV4, NF_INET_LOCAL_OUT, net, sk,
		      skb, NULL, vrf_dev, vrf_output_direct);

	if (likely(err == 1))
		err = vrf_output_direct(net, sk, skb);

	/* reset skb device */
	if (likely(err == 1))
		nf_reset_ct(skb);
	else
		skb = NULL;

	return skb;
}