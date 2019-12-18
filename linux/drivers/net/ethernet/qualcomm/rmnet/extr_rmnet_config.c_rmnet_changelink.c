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
typedef  size_t u16 ;
struct rmnet_priv {size_t mux_id; } ;
struct rmnet_port {int data_format; int /*<<< orphan*/ * muxed_ep; } ;
struct rmnet_endpoint {size_t mux_id; int /*<<< orphan*/  hlnode; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct ifla_rmnet_flags {int flags; int mask; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t IFLA_LINK ; 
 size_t IFLA_RMNET_FLAGS ; 
 size_t IFLA_RMNET_MUX_ID ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 struct rmnet_priv* netdev_priv (struct net_device*) ; 
 struct ifla_rmnet_flags* nla_data (struct nlattr*) ; 
 size_t nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct rmnet_endpoint* rmnet_get_endpoint (struct rmnet_port*,size_t) ; 
 struct rmnet_port* rmnet_get_port_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_is_real_dev_registered (struct net_device*) ; 

__attribute__((used)) static int rmnet_changelink(struct net_device *dev, struct nlattr *tb[],
			    struct nlattr *data[],
			    struct netlink_ext_ack *extack)
{
	struct rmnet_priv *priv = netdev_priv(dev);
	struct net_device *real_dev;
	struct rmnet_endpoint *ep;
	struct rmnet_port *port;
	u16 mux_id;

	if (!dev)
		return -ENODEV;

	real_dev = __dev_get_by_index(dev_net(dev),
				      nla_get_u32(tb[IFLA_LINK]));

	if (!real_dev || !rmnet_is_real_dev_registered(real_dev))
		return -ENODEV;

	port = rmnet_get_port_rtnl(real_dev);

	if (data[IFLA_RMNET_MUX_ID]) {
		mux_id = nla_get_u16(data[IFLA_RMNET_MUX_ID]);
		ep = rmnet_get_endpoint(port, priv->mux_id);
		if (!ep)
			return -ENODEV;

		hlist_del_init_rcu(&ep->hlnode);
		hlist_add_head_rcu(&ep->hlnode, &port->muxed_ep[mux_id]);

		ep->mux_id = mux_id;
		priv->mux_id = mux_id;
	}

	if (data[IFLA_RMNET_FLAGS]) {
		struct ifla_rmnet_flags *flags;

		flags = nla_data(data[IFLA_RMNET_FLAGS]);
		port->data_format = flags->flags & flags->mask;
	}

	return 0;
}