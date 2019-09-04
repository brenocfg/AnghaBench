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
struct net_device {int features; } ;
struct i40evf_adapter {int /*<<< orphan*/  aq_required; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I40EVF_FLAG_AQ_DISABLE_VLAN_STRIPPING ; 
 int /*<<< orphan*/  I40EVF_FLAG_AQ_ENABLE_VLAN_STRIPPING ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 scalar_t__ VLAN_ALLOWED (struct i40evf_adapter*) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40evf_set_features(struct net_device *netdev,
			       netdev_features_t features)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);

	/* Don't allow changing VLAN_RX flag when VLAN is set for VF
	 * and return an error in this case
	 */
	if (VLAN_ALLOWED(adapter)) {
		if (features & NETIF_F_HW_VLAN_CTAG_RX)
			adapter->aq_required |=
				I40EVF_FLAG_AQ_ENABLE_VLAN_STRIPPING;
		else
			adapter->aq_required |=
				I40EVF_FLAG_AQ_DISABLE_VLAN_STRIPPING;
	} else if ((netdev->features ^ features) & NETIF_F_HW_VLAN_CTAG_RX) {
		return -EINVAL;
	}

	return 0;
}