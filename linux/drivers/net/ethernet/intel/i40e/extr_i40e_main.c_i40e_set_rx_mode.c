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
struct net_device {int dummy; } ;
struct i40e_vsi {scalar_t__ current_netdev_flags; TYPE_2__* back; int /*<<< orphan*/  flags; TYPE_1__* netdev; int /*<<< orphan*/  mac_filter_hash_lock; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VSI_FLAG_FILTER_CHANGED ; 
 int /*<<< orphan*/  __I40E_MACVLAN_SYNC_PENDING ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_addr_sync ; 
 int /*<<< orphan*/  i40e_addr_unsync ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_set_rx_mode(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;

	spin_lock_bh(&vsi->mac_filter_hash_lock);

	__dev_uc_sync(netdev, i40e_addr_sync, i40e_addr_unsync);
	__dev_mc_sync(netdev, i40e_addr_sync, i40e_addr_unsync);

	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	/* check for other flag changes */
	if (vsi->current_netdev_flags != vsi->netdev->flags) {
		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
		set_bit(__I40E_MACVLAN_SYNC_PENDING, vsi->back->state);
	}
}