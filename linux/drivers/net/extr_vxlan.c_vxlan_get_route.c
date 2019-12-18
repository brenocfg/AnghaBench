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
typedef  scalar_t__ u8 ;
struct vxlan_sock {int dummy; } ;
struct vxlan_dev {int /*<<< orphan*/  net; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct TYPE_2__ {struct net_device* dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct ip_tunnel_info {int dummy; } ;
struct flowi4 {int flowi4_oif; void* saddr; void* fl4_sport; void* fl4_dport; void* daddr; int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_tos; } ;
struct dst_cache {int dummy; } ;
typedef  int /*<<< orphan*/  fl4 ;
typedef  void* __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ELOOP ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 struct rtable* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_TOS (scalar_t__) ; 
 struct rtable* dst_cache_get_ip4 (struct dst_cache*,void**) ; 
 int /*<<< orphan*/  dst_cache_set_ip4 (struct dst_cache*,TYPE_1__*,void*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int ip_tunnel_dst_cache_usable (struct sk_buff*,struct ip_tunnel_info const*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,void**) ; 

__attribute__((used)) static struct rtable *vxlan_get_route(struct vxlan_dev *vxlan, struct net_device *dev,
				      struct vxlan_sock *sock4,
				      struct sk_buff *skb, int oif, u8 tos,
				      __be32 daddr, __be32 *saddr, __be16 dport, __be16 sport,
				      struct dst_cache *dst_cache,
				      const struct ip_tunnel_info *info)
{
	bool use_cache = ip_tunnel_dst_cache_usable(skb, info);
	struct rtable *rt = NULL;
	struct flowi4 fl4;

	if (!sock4)
		return ERR_PTR(-EIO);

	if (tos && !info)
		use_cache = false;
	if (use_cache) {
		rt = dst_cache_get_ip4(dst_cache, saddr);
		if (rt)
			return rt;
	}

	memset(&fl4, 0, sizeof(fl4));
	fl4.flowi4_oif = oif;
	fl4.flowi4_tos = RT_TOS(tos);
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_proto = IPPROTO_UDP;
	fl4.daddr = daddr;
	fl4.saddr = *saddr;
	fl4.fl4_dport = dport;
	fl4.fl4_sport = sport;

	rt = ip_route_output_key(vxlan->net, &fl4);
	if (!IS_ERR(rt)) {
		if (rt->dst.dev == dev) {
			netdev_dbg(dev, "circular route to %pI4\n", &daddr);
			ip_rt_put(rt);
			return ERR_PTR(-ELOOP);
		}

		*saddr = fl4.saddr;
		if (use_cache)
			dst_cache_set_ip4(dst_cache, &rt->dst, fl4.saddr);
	} else {
		netdev_dbg(dev, "no route to %pI4\n", &daddr);
		return ERR_PTR(-ENETUNREACH);
	}
	return rt;
}