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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ eee_speeds_advertised; scalar_t__ eee_speeds_supported; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
struct ixgbe_adapter {int flags2; struct ixgbe_hw hw; } ;
struct ethtool_eee {scalar_t__ eee_enabled; scalar_t__ tx_lpi_enabled; scalar_t__ tx_lpi_timer; scalar_t__ advertised; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IXGBE_FLAG2_EEE_CAPABLE ; 
 int IXGBE_FLAG2_EEE_ENABLED ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int ixgbe_get_eee (struct net_device*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  ixgbe_reinit_locked (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  memset (struct ethtool_eee*,int /*<<< orphan*/ ,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_eee(struct net_device *netdev, struct ethtool_eee *edata)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	struct ethtool_eee eee_data;
	s32 ret_val;

	if (!(adapter->flags2 & IXGBE_FLAG2_EEE_CAPABLE))
		return -EOPNOTSUPP;

	memset(&eee_data, 0, sizeof(struct ethtool_eee));

	ret_val = ixgbe_get_eee(netdev, &eee_data);
	if (ret_val)
		return ret_val;

	if (eee_data.eee_enabled && !edata->eee_enabled) {
		if (eee_data.tx_lpi_enabled != edata->tx_lpi_enabled) {
			e_err(drv, "Setting EEE tx-lpi is not supported\n");
			return -EINVAL;
		}

		if (eee_data.tx_lpi_timer != edata->tx_lpi_timer) {
			e_err(drv,
			      "Setting EEE Tx LPI timer is not supported\n");
			return -EINVAL;
		}

		if (eee_data.advertised != edata->advertised) {
			e_err(drv,
			      "Setting EEE advertised speeds is not supported\n");
			return -EINVAL;
		}
	}

	if (eee_data.eee_enabled != edata->eee_enabled) {
		if (edata->eee_enabled) {
			adapter->flags2 |= IXGBE_FLAG2_EEE_ENABLED;
			hw->phy.eee_speeds_advertised =
						   hw->phy.eee_speeds_supported;
		} else {
			adapter->flags2 &= ~IXGBE_FLAG2_EEE_ENABLED;
			hw->phy.eee_speeds_advertised = 0;
		}

		/* reset link */
		if (netif_running(netdev))
			ixgbe_reinit_locked(adapter);
		else
			ixgbe_reset(adapter);
	}

	return 0;
}