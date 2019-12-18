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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ice_pf {int /*<<< orphan*/  int_name; TYPE_2__* pdev; int /*<<< orphan*/  state; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct ice_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 size_t ICE_ETH_TEST_EEPROM ; 
 size_t ICE_ETH_TEST_INTR ; 
 size_t ICE_ETH_TEST_LINK ; 
 size_t ICE_ETH_TEST_LOOP ; 
 size_t ICE_ETH_TEST_REG ; 
 int /*<<< orphan*/  __ICE_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ice_active_vfs (struct ice_pf*) ; 
 int ice_eeprom_test (struct net_device*) ; 
 int ice_intr_test (struct net_device*) ; 
 int ice_link_test (struct net_device*) ; 
 int ice_loopback_test (struct net_device*) ; 
 int ice_open (struct net_device*) ; 
 int ice_reg_test (struct net_device*) ; 
 int /*<<< orphan*/  ice_stop (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_self_test(struct net_device *netdev, struct ethtool_test *eth_test,
	      u64 *data)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	bool if_running = netif_running(netdev);
	struct ice_pf *pf = np->vsi->back;

	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		netdev_info(netdev, "offline testing starting\n");

		set_bit(__ICE_TESTING, pf->state);

		if (ice_active_vfs(pf)) {
			dev_warn(&pf->pdev->dev,
				 "Please take active VFs and Netqueues offline and restart the adapter before running NIC diagnostics\n");
			data[ICE_ETH_TEST_REG] = 1;
			data[ICE_ETH_TEST_EEPROM] = 1;
			data[ICE_ETH_TEST_INTR] = 1;
			data[ICE_ETH_TEST_LOOP] = 1;
			data[ICE_ETH_TEST_LINK] = 1;
			eth_test->flags |= ETH_TEST_FL_FAILED;
			clear_bit(__ICE_TESTING, pf->state);
			goto skip_ol_tests;
		}
		/* If the device is online then take it offline */
		if (if_running)
			/* indicate we're in test mode */
			ice_stop(netdev);

		data[ICE_ETH_TEST_LINK] = ice_link_test(netdev);
		data[ICE_ETH_TEST_EEPROM] = ice_eeprom_test(netdev);
		data[ICE_ETH_TEST_INTR] = ice_intr_test(netdev);
		data[ICE_ETH_TEST_LOOP] = ice_loopback_test(netdev);
		data[ICE_ETH_TEST_REG] = ice_reg_test(netdev);

		if (data[ICE_ETH_TEST_LINK] ||
		    data[ICE_ETH_TEST_EEPROM] ||
		    data[ICE_ETH_TEST_LOOP] ||
		    data[ICE_ETH_TEST_INTR] ||
		    data[ICE_ETH_TEST_REG])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__ICE_TESTING, pf->state);

		if (if_running) {
			int status = ice_open(netdev);

			if (status) {
				dev_err(&pf->pdev->dev,
					"Could not open device %s, err %d",
					pf->int_name, status);
			}
		}
	} else {
		/* Online tests */
		netdev_info(netdev, "online testing starting\n");

		data[ICE_ETH_TEST_LINK] = ice_link_test(netdev);
		if (data[ICE_ETH_TEST_LINK])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Offline only tests, not run in online; pass by default */
		data[ICE_ETH_TEST_REG] = 0;
		data[ICE_ETH_TEST_EEPROM] = 0;
		data[ICE_ETH_TEST_INTR] = 0;
		data[ICE_ETH_TEST_LOOP] = 0;
	}

skip_ol_tests:
	netdev_info(netdev, "testing finished\n");
}