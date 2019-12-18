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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct i40e_vsi {scalar_t__ type; int /*<<< orphan*/  mac_filter_hash_lock; struct i40e_pf* back; } ;
struct TYPE_4__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct i40e_hw {TYPE_2__ aq; TYPE_1__ mac; } ;
struct i40e_pf {int /*<<< orphan*/  state; struct i40e_hw hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  I40E_AQC_WRITE_TYPE_LAA_WOL ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_add_mac_filter (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_mac_address_write (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_del_mac_filter (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_service_event_schedule (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,...) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_set_mac(struct net_device *netdev, void *p)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, addr->sa_data)) {
		netdev_info(netdev, "already using mac address %pM\n",
			    addr->sa_data);
		return 0;
	}

	if (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(hw->mac.addr, addr->sa_data))
		netdev_info(netdev, "returning to hw mac address %pM\n",
			    hw->mac.addr);
	else
		netdev_info(netdev, "set new mac address %pM\n", addr->sa_data);

	/* Copy the address first, so that we avoid a possible race with
	 * .set_rx_mode().
	 * - Remove old address from MAC filter
	 * - Copy new address
	 * - Add new address to MAC filter
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	i40e_del_mac_filter(vsi, netdev->dev_addr);
	ether_addr_copy(netdev->dev_addr, addr->sa_data);
	i40e_add_mac_filter(vsi, netdev->dev_addr);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	if (vsi->type == I40E_VSI_MAIN) {
		i40e_status ret;

		ret = i40e_aq_mac_address_write(hw, I40E_AQC_WRITE_TYPE_LAA_WOL,
						addr->sa_data, NULL);
		if (ret)
			netdev_info(netdev, "Ignoring error from firmware on LAA update, status %s, AQ ret %s\n",
				    i40e_stat_str(hw, ret),
				    i40e_aq_str(hw, hw->aq.asq_last_status));
	}

	/* schedule our worker thread which will take care of
	 * applying the new filter changes
	 */
	i40e_service_event_schedule(pf);
	return 0;
}