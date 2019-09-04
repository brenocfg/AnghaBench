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
typedef  unsigned char u8 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_vfs; TYPE_2__* pdev; TYPE_1__* vfinfo; int /*<<< orphan*/  state; } ;
typedef  int s32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int pf_set_mac; unsigned char* vf_mac_addresses; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_valid_ether_addr (unsigned char*) ; 
 scalar_t__ is_zero_ether_addr (unsigned char*) ; 
 int ixgbe_del_mac_filter (struct ixgbe_adapter*,unsigned char*,int) ; 
 int ixgbe_set_vf_mac (struct ixgbe_adapter*,int,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbe_ndo_set_vf_mac(struct net_device *netdev, int vf, u8 *mac)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	s32 retval;

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	if (is_valid_ether_addr(mac)) {
		dev_info(&adapter->pdev->dev, "setting MAC %pM on VF %d\n",
			 mac, vf);
		dev_info(&adapter->pdev->dev, "Reload the VF driver to make this change effective.");

		retval = ixgbe_set_vf_mac(adapter, vf, mac);
		if (retval >= 0) {
			adapter->vfinfo[vf].pf_set_mac = true;

			if (test_bit(__IXGBE_DOWN, &adapter->state)) {
				dev_warn(&adapter->pdev->dev, "The VF MAC address has been set, but the PF device is not up.\n");
				dev_warn(&adapter->pdev->dev, "Bring the PF device up before attempting to use the VF device.\n");
			}
		} else {
			dev_warn(&adapter->pdev->dev, "The VF MAC address was NOT set due to invalid or duplicate MAC address.\n");
		}
	} else if (is_zero_ether_addr(mac)) {
		unsigned char *vf_mac_addr =
					   adapter->vfinfo[vf].vf_mac_addresses;

		/* nothing to do */
		if (is_zero_ether_addr(vf_mac_addr))
			return 0;

		dev_info(&adapter->pdev->dev, "removing MAC on VF %d\n", vf);

		retval = ixgbe_del_mac_filter(adapter, vf_mac_addr, vf);
		if (retval >= 0) {
			adapter->vfinfo[vf].pf_set_mac = false;
			memcpy(vf_mac_addr, mac, ETH_ALEN);
		} else {
			dev_warn(&adapter->pdev->dev, "Could NOT remove the VF MAC address.\n");
		}
	} else {
		retval = -EINVAL;
	}

	return retval;
}