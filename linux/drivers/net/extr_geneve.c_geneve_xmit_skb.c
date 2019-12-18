#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct net_device {int dummy; } ;
struct iphdr {int frag_off; } ;
struct ip_tunnel_key {int tun_flags; scalar_t__ ttl; int /*<<< orphan*/  tos; } ;
struct ip_tunnel_info {struct ip_tunnel_key key; scalar_t__ options_len; } ;
struct geneve_sock {TYPE_1__* sock; } ;
struct TYPE_5__ {int /*<<< orphan*/  tp_dst; } ;
struct TYPE_6__ {TYPE_2__ key; } ;
struct geneve_dev {scalar_t__ df; int /*<<< orphan*/  dev; int /*<<< orphan*/  net; TYPE_3__ info; scalar_t__ ttl_inherit; scalar_t__ collect_md; int /*<<< orphan*/  sock4; } ;
struct flowi4 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi4_tos; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  scalar_t__ __u8 ;
typedef  int __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ GENEVE_DF_INHERIT ; 
 scalar_t__ GENEVE_DF_SET ; 
 scalar_t__ GENEVE_IPV4_HLEN ; 
 int /*<<< orphan*/  IP_DF ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int geneve_build_skb (int /*<<< orphan*/ *,struct sk_buff*,struct ip_tunnel_info const*,int,int) ; 
 struct rtable* geneve_get_v4_rt (struct sk_buff*,struct net_device*,struct geneve_sock*,struct flowi4*,struct ip_tunnel_info const*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ip4_dst_hoplimit (int /*<<< orphan*/ *) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_tunnel_ecn_encap (int /*<<< orphan*/ ,struct iphdr*,struct sk_buff*) ; 
 scalar_t__ ip_tunnel_get_ttl (struct iphdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct geneve_sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tunnel_check_pmtu (struct sk_buff*,int /*<<< orphan*/ *,scalar_t__) ; 
 int udp_flow_src_port (int /*<<< orphan*/ ,struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udp_tunnel_xmit_skb (struct rtable*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int geneve_xmit_skb(struct sk_buff *skb, struct net_device *dev,
			   struct geneve_dev *geneve,
			   const struct ip_tunnel_info *info)
{
	bool xnet = !net_eq(geneve->net, dev_net(geneve->dev));
	struct geneve_sock *gs4 = rcu_dereference(geneve->sock4);
	const struct ip_tunnel_key *key = &info->key;
	struct rtable *rt;
	struct flowi4 fl4;
	__u8 tos, ttl;
	__be16 df = 0;
	__be16 sport;
	int err;

	rt = geneve_get_v4_rt(skb, dev, gs4, &fl4, info);
	if (IS_ERR(rt))
		return PTR_ERR(rt);

	skb_tunnel_check_pmtu(skb, &rt->dst,
			      GENEVE_IPV4_HLEN + info->options_len);

	sport = udp_flow_src_port(geneve->net, skb, 1, USHRT_MAX, true);
	if (geneve->collect_md) {
		tos = ip_tunnel_ecn_encap(key->tos, ip_hdr(skb), skb);
		ttl = key->ttl;

		df = key->tun_flags & TUNNEL_DONT_FRAGMENT ? htons(IP_DF) : 0;
	} else {
		tos = ip_tunnel_ecn_encap(fl4.flowi4_tos, ip_hdr(skb), skb);
		if (geneve->ttl_inherit)
			ttl = ip_tunnel_get_ttl(ip_hdr(skb), skb);
		else
			ttl = key->ttl;
		ttl = ttl ? : ip4_dst_hoplimit(&rt->dst);

		if (geneve->df == GENEVE_DF_SET) {
			df = htons(IP_DF);
		} else if (geneve->df == GENEVE_DF_INHERIT) {
			struct ethhdr *eth = eth_hdr(skb);

			if (ntohs(eth->h_proto) == ETH_P_IPV6) {
				df = htons(IP_DF);
			} else if (ntohs(eth->h_proto) == ETH_P_IP) {
				struct iphdr *iph = ip_hdr(skb);

				if (iph->frag_off & htons(IP_DF))
					df = htons(IP_DF);
			}
		}
	}

	err = geneve_build_skb(&rt->dst, skb, info, xnet, sizeof(struct iphdr));
	if (unlikely(err))
		return err;

	udp_tunnel_xmit_skb(rt, gs4->sock->sk, skb, fl4.saddr, fl4.daddr,
			    tos, ttl, df, sport, geneve->info.key.tp_dst,
			    !net_eq(geneve->net, dev_net(geneve->dev)),
			    !(info->key.tun_flags & TUNNEL_CSUM));
	return 0;
}