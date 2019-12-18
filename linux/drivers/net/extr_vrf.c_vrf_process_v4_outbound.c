#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_6__ {struct net_device* dev; } ;
struct rtable {TYPE_2__ dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct iphdr {scalar_t__ saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tos; } ;
struct flowi4 {int flowi4_flags; scalar_t__ saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_iif; int /*<<< orphan*/  flowi4_oif; } ;
typedef  int netdev_tx_t ;
typedef  int /*<<< orphan*/  fl4 ;
struct TYPE_7__ {struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int FLOWI_FLAG_ANYSRC ; 
 int FLOWI_FLAG_SKIP_NH_OIF ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 scalar_t__ inet_select_addr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct rtable* ip_route_output_flow (struct net*,struct flowi4*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_xmit_eval (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vrf_ip_local_out (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int vrf_local_xmit (struct sk_buff*,struct net_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  vrf_tx_error (struct net_device*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t vrf_process_v4_outbound(struct sk_buff *skb,
					   struct net_device *vrf_dev)
{
	struct iphdr *ip4h;
	int ret = NET_XMIT_DROP;
	struct flowi4 fl4;
	struct net *net = dev_net(vrf_dev);
	struct rtable *rt;

	if (!pskb_may_pull(skb, ETH_HLEN + sizeof(struct iphdr)))
		goto err;

	ip4h = ip_hdr(skb);

	memset(&fl4, 0, sizeof(fl4));
	/* needed to match OIF rule */
	fl4.flowi4_oif = vrf_dev->ifindex;
	fl4.flowi4_iif = LOOPBACK_IFINDEX;
	fl4.flowi4_tos = RT_TOS(ip4h->tos);
	fl4.flowi4_flags = FLOWI_FLAG_ANYSRC | FLOWI_FLAG_SKIP_NH_OIF;
	fl4.flowi4_proto = ip4h->protocol;
	fl4.daddr = ip4h->daddr;
	fl4.saddr = ip4h->saddr;

	rt = ip_route_output_flow(net, &fl4, NULL);
	if (IS_ERR(rt))
		goto err;

	skb_dst_drop(skb);

	/* if dst.dev is loopback or the VRF device again this is locally
	 * originated traffic destined to a local address. Short circuit
	 * to Rx path
	 */
	if (rt->dst.dev == vrf_dev)
		return vrf_local_xmit(skb, vrf_dev, &rt->dst);

	skb_dst_set(skb, &rt->dst);

	/* strip the ethernet header added for pass through VRF device */
	__skb_pull(skb, skb_network_offset(skb));

	if (!ip4h->saddr) {
		ip4h->saddr = inet_select_addr(skb_dst(skb)->dev, 0,
					       RT_SCOPE_LINK);
	}

	ret = vrf_ip_local_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	if (unlikely(net_xmit_eval(ret)))
		vrf_dev->stats.tx_errors++;
	else
		ret = NET_XMIT_SUCCESS;

out:
	return ret;
err:
	vrf_tx_error(vrf_dev, skb);
	goto out;
}