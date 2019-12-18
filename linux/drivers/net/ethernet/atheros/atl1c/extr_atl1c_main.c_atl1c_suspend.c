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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct atl1c_hw {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  flags; scalar_t__ wol; struct atl1c_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  atl1c_disable_l0s_l1 (struct atl1c_hw*) ; 
 int /*<<< orphan*/  atl1c_down (struct atl1c_adapter*) ; 
 scalar_t__ atl1c_phy_to_ps_link (struct atl1c_hw*) ; 
 int /*<<< orphan*/  atl1c_power_saving (struct atl1c_hw*,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1c_suspend(struct device *dev)
{
	struct net_device *netdev = dev_get_drvdata(dev);
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct atl1c_hw *hw = &adapter->hw;
	u32 wufc = adapter->wol;

	atl1c_disable_l0s_l1(hw);
	if (netif_running(netdev)) {
		WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
		atl1c_down(adapter);
	}
	netif_device_detach(netdev);

	if (wufc)
		if (atl1c_phy_to_ps_link(hw) != 0)
			dev_dbg(dev, "phy power saving failed");

	atl1c_power_saving(hw, wufc);

	return 0;
}