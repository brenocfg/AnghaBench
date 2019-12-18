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
typedef  int u16 ;
struct nfp_tun_offloaded_mac {int index; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  repr_list; int /*<<< orphan*/  addr; scalar_t__ bridge_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_off_ids; int /*<<< orphan*/  offloaded_macs; } ;
struct nfp_flower_priv {TYPE_1__ tun; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NFP_MAX_MAC_INDEX ; 
 int NFP_TUN_PRE_TUN_IDX_BIT ; 
 int __nfp_tunnel_offload_mac (struct nfp_app*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nfp_tun_offloaded_mac*) ; 
 struct nfp_tun_offloaded_mac* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_flower_is_supported_bridge (struct net_device*) ; 
 int nfp_tunnel_get_global_mac_idx_from_ida (int) ; 
 int nfp_tunnel_get_mac_idx_from_phy_port_id (int) ; 
 scalar_t__ nfp_tunnel_is_mac_idx_global (int) ; 
 struct nfp_tun_offloaded_mac* nfp_tunnel_lookup_offloaded_macs (struct nfp_app*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_tunnel_offloaded_macs_inc_ref_and_link (struct nfp_tun_offloaded_mac*,struct net_device*,int) ; 
 int /*<<< orphan*/  offloaded_macs_params ; 
 scalar_t__ rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_tunnel_add_shared_mac(struct nfp_app *app, struct net_device *netdev,
			  int port, bool mod)
{
	struct nfp_flower_priv *priv = app->priv;
	int ida_idx = NFP_MAX_MAC_INDEX, err;
	struct nfp_tun_offloaded_mac *entry;
	u16 nfp_mac_idx = 0;

	entry = nfp_tunnel_lookup_offloaded_macs(app, netdev->dev_addr);
	if (entry && nfp_tunnel_is_mac_idx_global(entry->index)) {
		if (entry->bridge_count ||
		    !nfp_flower_is_supported_bridge(netdev)) {
			nfp_tunnel_offloaded_macs_inc_ref_and_link(entry,
								   netdev, mod);
			return 0;
		}

		/* MAC is global but matches need to go to pre_tun table. */
		nfp_mac_idx = entry->index | NFP_TUN_PRE_TUN_IDX_BIT;
	}

	if (!nfp_mac_idx) {
		/* Assign a global index if non-repr or MAC is now shared. */
		if (entry || !port) {
			ida_idx = ida_simple_get(&priv->tun.mac_off_ids, 0,
						 NFP_MAX_MAC_INDEX, GFP_KERNEL);
			if (ida_idx < 0)
				return ida_idx;

			nfp_mac_idx =
				nfp_tunnel_get_global_mac_idx_from_ida(ida_idx);

			if (nfp_flower_is_supported_bridge(netdev))
				nfp_mac_idx |= NFP_TUN_PRE_TUN_IDX_BIT;

		} else {
			nfp_mac_idx =
				nfp_tunnel_get_mac_idx_from_phy_port_id(port);
		}
	}

	if (!entry) {
		entry = kzalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry) {
			err = -ENOMEM;
			goto err_free_ida;
		}

		ether_addr_copy(entry->addr, netdev->dev_addr);
		INIT_LIST_HEAD(&entry->repr_list);

		if (rhashtable_insert_fast(&priv->tun.offloaded_macs,
					   &entry->ht_node,
					   offloaded_macs_params)) {
			err = -ENOMEM;
			goto err_free_entry;
		}
	}

	err = __nfp_tunnel_offload_mac(app, netdev->dev_addr,
				       nfp_mac_idx, false);
	if (err) {
		/* If not shared then free. */
		if (!entry->ref_count)
			goto err_remove_hash;
		goto err_free_ida;
	}

	entry->index = nfp_mac_idx;
	nfp_tunnel_offloaded_macs_inc_ref_and_link(entry, netdev, mod);

	return 0;

err_remove_hash:
	rhashtable_remove_fast(&priv->tun.offloaded_macs, &entry->ht_node,
			       offloaded_macs_params);
err_free_entry:
	kfree(entry);
err_free_ida:
	if (ida_idx != NFP_MAX_MAC_INDEX)
		ida_simple_remove(&priv->tun.mac_off_ids, ida_idx);

	return err;
}