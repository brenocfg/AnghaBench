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
struct nfp_repr {struct nfp_flower_repr_priv* app_priv; struct nfp_app* app; } ;
struct nfp_flower_repr_priv {int mac_offloaded; int /*<<< orphan*/ * offloaded_mac_addr; scalar_t__ on_bridge; } ;
struct nfp_flower_non_repr_priv {int mac_offloaded; int /*<<< orphan*/ * offloaded_mac_addr; } ;
struct nfp_app {int dummy; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
typedef  enum nfp_flower_mac_offload_cmd { ____Placeholder_nfp_flower_mac_offload_cmd } nfp_flower_mac_offload_cmd ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  NFP_TUNNEL_MAC_OFFLOAD_ADD 130 
#define  NFP_TUNNEL_MAC_OFFLOAD_DEL 129 
#define  NFP_TUNNEL_MAC_OFFLOAD_MOD 128 
 int /*<<< orphan*/  __nfp_flower_non_repr_priv_get (struct nfp_flower_non_repr_priv*) ; 
 int /*<<< orphan*/  __nfp_flower_non_repr_priv_put (struct nfp_flower_non_repr_priv*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 scalar_t__ nfp_fl_is_netdev_to_offload (struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*,int /*<<< orphan*/ ) ; 
 struct nfp_flower_non_repr_priv* nfp_flower_non_repr_priv_get (struct nfp_app*,struct net_device*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int nfp_repr_get_port_id (struct net_device*) ; 
 int nfp_tunnel_add_shared_mac (struct nfp_app*,struct net_device*,int,int) ; 
 int nfp_tunnel_del_shared_mac (struct nfp_app*,struct net_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfp_tunnel_port_is_phy_repr (int) ; 

__attribute__((used)) static int
nfp_tunnel_offload_mac(struct nfp_app *app, struct net_device *netdev,
		       enum nfp_flower_mac_offload_cmd cmd)
{
	struct nfp_flower_non_repr_priv *nr_priv = NULL;
	bool non_repr = false, *mac_offloaded;
	u8 *off_mac = NULL;
	int err, port = 0;

	if (nfp_netdev_is_nfp_repr(netdev)) {
		struct nfp_flower_repr_priv *repr_priv;
		struct nfp_repr *repr;

		repr = netdev_priv(netdev);
		if (repr->app != app)
			return 0;

		repr_priv = repr->app_priv;
		if (repr_priv->on_bridge)
			return 0;

		mac_offloaded = &repr_priv->mac_offloaded;
		off_mac = &repr_priv->offloaded_mac_addr[0];
		port = nfp_repr_get_port_id(netdev);
		if (!nfp_tunnel_port_is_phy_repr(port))
			return 0;
	} else if (nfp_fl_is_netdev_to_offload(netdev)) {
		nr_priv = nfp_flower_non_repr_priv_get(app, netdev);
		if (!nr_priv)
			return -ENOMEM;

		mac_offloaded = &nr_priv->mac_offloaded;
		off_mac = &nr_priv->offloaded_mac_addr[0];
		non_repr = true;
	} else {
		return 0;
	}

	if (!is_valid_ether_addr(netdev->dev_addr)) {
		err = -EINVAL;
		goto err_put_non_repr_priv;
	}

	if (cmd == NFP_TUNNEL_MAC_OFFLOAD_MOD && !*mac_offloaded)
		cmd = NFP_TUNNEL_MAC_OFFLOAD_ADD;

	switch (cmd) {
	case NFP_TUNNEL_MAC_OFFLOAD_ADD:
		err = nfp_tunnel_add_shared_mac(app, netdev, port, false);
		if (err)
			goto err_put_non_repr_priv;

		if (non_repr)
			__nfp_flower_non_repr_priv_get(nr_priv);

		*mac_offloaded = true;
		ether_addr_copy(off_mac, netdev->dev_addr);
		break;
	case NFP_TUNNEL_MAC_OFFLOAD_DEL:
		/* Only attempt delete if add was successful. */
		if (!*mac_offloaded)
			break;

		if (non_repr)
			__nfp_flower_non_repr_priv_put(nr_priv);

		*mac_offloaded = false;

		err = nfp_tunnel_del_shared_mac(app, netdev, netdev->dev_addr,
						false);
		if (err)
			goto err_put_non_repr_priv;

		break;
	case NFP_TUNNEL_MAC_OFFLOAD_MOD:
		/* Ignore if changing to the same address. */
		if (ether_addr_equal(netdev->dev_addr, off_mac))
			break;

		err = nfp_tunnel_add_shared_mac(app, netdev, port, true);
		if (err)
			goto err_put_non_repr_priv;

		/* Delete the previous MAC address. */
		err = nfp_tunnel_del_shared_mac(app, netdev, off_mac, true);
		if (err)
			nfp_flower_cmsg_warn(app, "Failed to remove offload of replaced MAC addr on %s.\n",
					     netdev_name(netdev));

		ether_addr_copy(off_mac, netdev->dev_addr);
		break;
	default:
		err = -EINVAL;
		goto err_put_non_repr_priv;
	}

	if (non_repr)
		__nfp_flower_non_repr_priv_put(nr_priv);

	return 0;

err_put_non_repr_priv:
	if (non_repr)
		__nfp_flower_non_repr_priv_put(nr_priv);

	return err;
}