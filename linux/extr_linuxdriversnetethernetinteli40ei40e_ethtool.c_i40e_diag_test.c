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
struct i40e_pf {int /*<<< orphan*/  state; TYPE_2__* pdev; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 size_t I40E_ETH_TEST_EEPROM ; 
 size_t I40E_ETH_TEST_INTR ; 
 size_t I40E_ETH_TEST_LINK ; 
 size_t I40E_ETH_TEST_REG ; 
 int /*<<< orphan*/  __I40E_PF_RESET_REQUESTED ; 
 int /*<<< orphan*/  __I40E_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ i40e_active_vfs (struct i40e_pf*) ; 
 scalar_t__ i40e_active_vmdqs (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_close (struct net_device*) ; 
 int /*<<< orphan*/  i40e_do_reset (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ i40e_eeprom_test (struct net_device*,int*) ; 
 scalar_t__ i40e_intr_test (struct net_device*,int*) ; 
 scalar_t__ i40e_link_test (struct net_device*,int*) ; 
 int /*<<< orphan*/  i40e_open (struct net_device*) ; 
 scalar_t__ i40e_reg_test (struct net_device*,int*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct i40e_pf*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_diag_test(struct net_device *netdev,
			   struct ethtool_test *eth_test, u64 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	bool if_running = netif_running(netdev);
	struct i40e_pf *pf = np->vsi->back;

	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */
		netif_info(pf, drv, netdev, "offline testing starting\n");

		set_bit(__I40E_TESTING, pf->state);

		if (i40e_active_vfs(pf) || i40e_active_vmdqs(pf)) {
			dev_warn(&pf->pdev->dev,
				 "Please take active VFs and Netqueues offline and restart the adapter before running NIC diagnostics\n");
			data[I40E_ETH_TEST_REG]		= 1;
			data[I40E_ETH_TEST_EEPROM]	= 1;
			data[I40E_ETH_TEST_INTR]	= 1;
			data[I40E_ETH_TEST_LINK]	= 1;
			eth_test->flags |= ETH_TEST_FL_FAILED;
			clear_bit(__I40E_TESTING, pf->state);
			goto skip_ol_tests;
		}

		/* If the device is online then take it offline */
		if (if_running)
			/* indicate we're in test mode */
			i40e_close(netdev);
		else
			/* This reset does not affect link - if it is
			 * changed to a type of reset that does affect
			 * link then the following link test would have
			 * to be moved to before the reset
			 */
			i40e_do_reset(pf, BIT(__I40E_PF_RESET_REQUESTED), true);

		if (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (i40e_eeprom_test(netdev, &data[I40E_ETH_TEST_EEPROM]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (i40e_intr_test(netdev, &data[I40E_ETH_TEST_INTR]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* run reg test last, a reset is required after it */
		if (i40e_reg_test(netdev, &data[I40E_ETH_TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__I40E_TESTING, pf->state);
		i40e_do_reset(pf, BIT(__I40E_PF_RESET_REQUESTED), true);

		if (if_running)
			i40e_open(netdev);
	} else {
		/* Online tests */
		netif_info(pf, drv, netdev, "online testing starting\n");

		if (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Offline only tests, not run in online; pass by default */
		data[I40E_ETH_TEST_REG] = 0;
		data[I40E_ETH_TEST_EEPROM] = 0;
		data[I40E_ETH_TEST_INTR] = 0;
	}

skip_ol_tests:

	netif_info(pf, drv, netdev, "testing finished\n");
}