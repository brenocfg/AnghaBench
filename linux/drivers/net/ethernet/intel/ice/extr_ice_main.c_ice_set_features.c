#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct ice_vsi {TYPE_2__* back; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ice_cfg_vlan_pruning (struct ice_vsi*,int,int) ; 
 scalar_t__ ice_is_safe_mode (TYPE_2__*) ; 
 int ice_vsi_manage_rss_lut (struct ice_vsi*,int) ; 
 int ice_vsi_manage_vlan_insertion (struct ice_vsi*) ; 
 int ice_vsi_manage_vlan_stripping (struct ice_vsi*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ice_set_features(struct net_device *netdev, netdev_features_t features)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	int ret = 0;

	/* Don't set any netdev advanced features with device in Safe Mode */
	if (ice_is_safe_mode(vsi->back)) {
		dev_err(&vsi->back->pdev->dev,
			"Device is in Safe Mode - not enabling advanced netdev features\n");
		return ret;
	}

	/* Multiple features can be changed in one call so keep features in
	 * separate if/else statements to guarantee each feature is checked
	 */
	if (features & NETIF_F_RXHASH && !(netdev->features & NETIF_F_RXHASH))
		ret = ice_vsi_manage_rss_lut(vsi, true);
	else if (!(features & NETIF_F_RXHASH) &&
		 netdev->features & NETIF_F_RXHASH)
		ret = ice_vsi_manage_rss_lut(vsi, false);

	if ((features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_RX))
		ret = ice_vsi_manage_vlan_stripping(vsi, true);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_RX) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_RX))
		ret = ice_vsi_manage_vlan_stripping(vsi, false);

	if ((features & NETIF_F_HW_VLAN_CTAG_TX) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_TX))
		ret = ice_vsi_manage_vlan_insertion(vsi);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_TX) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_TX))
		ret = ice_vsi_manage_vlan_insertion(vsi);

	if ((features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		ret = ice_cfg_vlan_pruning(vsi, true, false);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		ret = ice_cfg_vlan_pruning(vsi, false, false);

	return ret;
}