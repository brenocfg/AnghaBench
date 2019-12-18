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
struct sockaddr {scalar_t__ sa_data; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  addr_len; } ;
struct ice_vsi {int /*<<< orphan*/  netdev; struct ice_pf* back; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 int /*<<< orphan*/  ICE_AQC_MAN_MAC_UPDATE_LAA_WOL ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_aq_manage_mac_write (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_is_reset_in_progress (int /*<<< orphan*/ ) ; 
 int ice_vsi_cfg_mac_fltr (struct ice_vsi*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ *,...) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_set_mac_address(struct net_device *netdev, void *pi)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	struct sockaddr *addr = pi;
	enum ice_status status;
	u8 flags = 0;
	int err = 0;
	u8 *mac;

	mac = (u8 *)addr->sa_data;

	if (!is_valid_ether_addr(mac))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, mac)) {
		netdev_warn(netdev, "already using mac %pM\n", mac);
		return 0;
	}

	if (test_bit(__ICE_DOWN, pf->state) ||
	    ice_is_reset_in_progress(pf->state)) {
		netdev_err(netdev, "can't set mac %pM. device not ready\n",
			   mac);
		return -EBUSY;
	}

	/* When we change the MAC address we also have to change the MAC address
	 * based filter rules that were created previously for the old MAC
	 * address. So first, we remove the old filter rule using ice_remove_mac
	 * and then create a new filter rule using ice_add_mac via
	 * ice_vsi_cfg_mac_fltr function call for both add and/or remove
	 * filters.
	 */
	status = ice_vsi_cfg_mac_fltr(vsi, netdev->dev_addr, false);
	if (status) {
		err = -EADDRNOTAVAIL;
		goto err_update_filters;
	}

	status = ice_vsi_cfg_mac_fltr(vsi, mac, true);
	if (status) {
		err = -EADDRNOTAVAIL;
		goto err_update_filters;
	}

err_update_filters:
	if (err) {
		netdev_err(netdev, "can't set MAC %pM. filter update failed\n",
			   mac);
		return err;
	}

	/* change the netdev's MAC address */
	memcpy(netdev->dev_addr, mac, netdev->addr_len);
	netdev_dbg(vsi->netdev, "updated MAC address to %pM\n",
		   netdev->dev_addr);

	/* write new MAC address to the firmware */
	flags = ICE_AQC_MAN_MAC_UPDATE_LAA_WOL;
	status = ice_aq_manage_mac_write(hw, mac, flags, NULL);
	if (status) {
		netdev_err(netdev, "can't set MAC %pM. write to firmware failed error %d\n",
			   mac, status);
	}
	return 0;
}