#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_3__ dev; } ;
struct ethtool_eee {scalar_t__ tx_lpi_enabled; scalar_t__ tx_lpi_timer; int advertised; int /*<<< orphan*/  eee_enabled; } ;
struct TYPE_4__ {int eee_disable; } ;
struct TYPE_5__ {TYPE_1__ ich8lan; } ;
struct e1000_hw {TYPE_2__ dev_spec; } ;
struct e1000_adapter {int /*<<< orphan*/  eee_advert; struct e1000_hw hw; } ;
typedef  int s32 ;

/* Variables and functions */
 int ADVERTISE_1000_FULL ; 
 int ADVERTISE_100_FULL ; 
 int EINVAL ; 
 int e1000e_get_eee (struct net_device*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  e1000e_reinit_locked (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int /*<<< orphan*/  ethtool_adv_to_mmd_eee_adv_t (int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000e_set_eee(struct net_device *netdev, struct ethtool_eee *edata)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct ethtool_eee eee_curr;
	s32 ret_val;

	ret_val = e1000e_get_eee(netdev, &eee_curr);
	if (ret_val)
		return ret_val;

	if (eee_curr.tx_lpi_enabled != edata->tx_lpi_enabled) {
		e_err("Setting EEE tx-lpi is not supported\n");
		return -EINVAL;
	}

	if (eee_curr.tx_lpi_timer != edata->tx_lpi_timer) {
		e_err("Setting EEE Tx LPI timer is not supported\n");
		return -EINVAL;
	}

	if (edata->advertised & ~(ADVERTISE_100_FULL | ADVERTISE_1000_FULL)) {
		e_err("EEE advertisement supports only 100TX and/or 1000T full-duplex\n");
		return -EINVAL;
	}

	adapter->eee_advert = ethtool_adv_to_mmd_eee_adv_t(edata->advertised);

	hw->dev_spec.ich8lan.eee_disable = !edata->eee_enabled;

	pm_runtime_get_sync(netdev->dev.parent);

	/* reset the link */
	if (netif_running(netdev))
		e1000e_reinit_locked(adapter);
	else
		e1000e_reset(adapter);

	pm_runtime_put_sync(netdev->dev.parent);

	return 0;
}