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
struct nfp_tun_offloaded_mac {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  bridge_count; int /*<<< orphan*/  repr_list; } ;
struct nfp_repr {struct nfp_flower_repr_priv* app_priv; } ;
struct nfp_flower_repr_priv {int /*<<< orphan*/  mac_list; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 scalar_t__ nfp_flower_is_supported_bridge (struct net_device*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 

__attribute__((used)) static void
nfp_tunnel_offloaded_macs_inc_ref_and_link(struct nfp_tun_offloaded_mac *entry,
					   struct net_device *netdev, bool mod)
{
	if (nfp_netdev_is_nfp_repr(netdev)) {
		struct nfp_flower_repr_priv *repr_priv;
		struct nfp_repr *repr;

		repr = netdev_priv(netdev);
		repr_priv = repr->app_priv;

		/* If modifing MAC, remove repr from old list first. */
		if (mod)
			list_del(&repr_priv->mac_list);

		list_add_tail(&repr_priv->mac_list, &entry->repr_list);
	} else if (nfp_flower_is_supported_bridge(netdev)) {
		entry->bridge_count++;
	}

	entry->ref_count++;
}