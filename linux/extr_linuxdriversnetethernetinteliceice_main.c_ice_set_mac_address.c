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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {scalar_t__ sa_data; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  addr_len; } ;
struct ice_vsi {int /*<<< orphan*/  netdev; struct ice_pf* back; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {TYPE_1__* pdev; int /*<<< orphan*/  state; struct ice_hw hw; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 int /*<<< orphan*/  ICE_AQC_MAN_MAC_UPDATE_LAA_WOL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  a_mac_list ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_add_mac (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int ice_add_mac_to_list (struct ice_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ice_aq_manage_mac_write (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_is_reset_recovery_pending (int /*<<< orphan*/ ) ; 
 int ice_remove_mac (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ *) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_mac_list ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_set_mac_address(struct net_device *netdev, void *pi)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	struct sockaddr *addr = pi;
	enum ice_status status;
	LIST_HEAD(a_mac_list);
	LIST_HEAD(r_mac_list);
	u8 flags = 0;
	int err;
	u8 *mac;

	mac = (u8 *)addr->sa_data;

	if (!is_valid_ether_addr(mac))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, mac)) {
		netdev_warn(netdev, "already using mac %pM\n", mac);
		return 0;
	}

	if (test_bit(__ICE_DOWN, pf->state) ||
	    ice_is_reset_recovery_pending(pf->state)) {
		netdev_err(netdev, "can't set mac %pM. device not ready\n",
			   mac);
		return -EBUSY;
	}

	/* When we change the mac address we also have to change the mac address
	 * based filter rules that were created previously for the old mac
	 * address. So first, we remove the old filter rule using ice_remove_mac
	 * and then create a new filter rule using ice_add_mac. Note that for
	 * both these operations, we first need to form a "list" of mac
	 * addresses (even though in this case, we have only 1 mac address to be
	 * added/removed) and this done using ice_add_mac_to_list. Depending on
	 * the ensuing operation this "list" of mac addresses is either to be
	 * added or removed from the filter.
	 */
	err = ice_add_mac_to_list(vsi, &r_mac_list, netdev->dev_addr);
	if (err) {
		err = -EADDRNOTAVAIL;
		goto free_lists;
	}

	status = ice_remove_mac(hw, &r_mac_list);
	if (status) {
		err = -EADDRNOTAVAIL;
		goto free_lists;
	}

	err = ice_add_mac_to_list(vsi, &a_mac_list, mac);
	if (err) {
		err = -EADDRNOTAVAIL;
		goto free_lists;
	}

	status = ice_add_mac(hw, &a_mac_list);
	if (status) {
		err = -EADDRNOTAVAIL;
		goto free_lists;
	}

free_lists:
	/* free list entries */
	ice_free_fltr_list(&pf->pdev->dev, &r_mac_list);
	ice_free_fltr_list(&pf->pdev->dev, &a_mac_list);

	if (err) {
		netdev_err(netdev, "can't set mac %pM. filter update failed\n",
			   mac);
		return err;
	}

	/* change the netdev's mac address */
	memcpy(netdev->dev_addr, mac, netdev->addr_len);
	netdev_dbg(vsi->netdev, "updated mac address to %pM\n",
		   netdev->dev_addr);

	/* write new mac address to the firmware */
	flags = ICE_AQC_MAN_MAC_UPDATE_LAA_WOL;
	status = ice_aq_manage_mac_write(hw, mac, flags, NULL);
	if (status) {
		netdev_err(netdev, "can't set mac %pM. write to firmware failed.\n",
			   mac);
	}
	return 0;
}