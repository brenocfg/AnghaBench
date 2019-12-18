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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int max_mtu; int needed_headroom; } ;
struct net {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_tunnel_info {int /*<<< orphan*/  dst_cache; } ;
struct geneve_net {int /*<<< orphan*/  geneve_list; } ;
struct geneve_dev {int collect_md; int use_udp6_rx_checksums; int ttl_inherit; int df; int /*<<< orphan*/  next; struct ip_tunnel_info info; struct net_device* dev; struct net* net; } ;
typedef  enum ifla_geneve_df { ____Placeholder_ifla_geneve_df } ifla_geneve_df ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int ETH_HLEN ; 
 int GENEVE_BASE_HLEN ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  dst_cache_reset (int /*<<< orphan*/ *) ; 
 struct geneve_dev* geneve_find_dev (struct geneve_net*,struct ip_tunnel_info const*,int*,int*) ; 
 int /*<<< orphan*/  geneve_net_id ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info const*) ; 
 int /*<<< orphan*/  is_tnl_info_zero (struct ip_tunnel_info const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct geneve_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct geneve_dev* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int geneve_configure(struct net *net, struct net_device *dev,
			    struct netlink_ext_ack *extack,
			    const struct ip_tunnel_info *info,
			    bool metadata, bool ipv6_rx_csum,
			    bool ttl_inherit, enum ifla_geneve_df df)
{
	struct geneve_net *gn = net_generic(net, geneve_net_id);
	struct geneve_dev *t, *geneve = netdev_priv(dev);
	bool tun_collect_md, tun_on_same_port;
	int err, encap_len;

	if (metadata && !is_tnl_info_zero(info)) {
		NL_SET_ERR_MSG(extack,
			       "Device is externally controlled, so attributes (VNI, Port, and so on) must not be specified");
		return -EINVAL;
	}

	geneve->net = net;
	geneve->dev = dev;

	t = geneve_find_dev(gn, info, &tun_on_same_port, &tun_collect_md);
	if (t)
		return -EBUSY;

	/* make enough headroom for basic scenario */
	encap_len = GENEVE_BASE_HLEN + ETH_HLEN;
	if (!metadata && ip_tunnel_info_af(info) == AF_INET) {
		encap_len += sizeof(struct iphdr);
		dev->max_mtu -= sizeof(struct iphdr);
	} else {
		encap_len += sizeof(struct ipv6hdr);
		dev->max_mtu -= sizeof(struct ipv6hdr);
	}
	dev->needed_headroom = encap_len + ETH_HLEN;

	if (metadata) {
		if (tun_on_same_port) {
			NL_SET_ERR_MSG(extack,
				       "There can be only one externally controlled device on a destination port");
			return -EPERM;
		}
	} else {
		if (tun_collect_md) {
			NL_SET_ERR_MSG(extack,
				       "There already exists an externally controlled device on this destination port");
			return -EPERM;
		}
	}

	dst_cache_reset(&geneve->info.dst_cache);
	geneve->info = *info;
	geneve->collect_md = metadata;
	geneve->use_udp6_rx_checksums = ipv6_rx_csum;
	geneve->ttl_inherit = ttl_inherit;
	geneve->df = df;

	err = register_netdevice(dev);
	if (err)
		return err;

	list_add(&geneve->next, &gn->geneve_list);
	return 0;
}