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
struct TYPE_4__ {int /*<<< orphan*/  hw_addr; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  state; TYPE_2__ hw; TYPE_1__* pdev; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 scalar_t__ IXGBE_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBEVF_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hw_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ixgbevf_close (struct net_device*) ; 
 scalar_t__ ixgbevf_link_test (struct ixgbevf_adapter*,int*) ; 
 int /*<<< orphan*/  ixgbevf_open (struct net_device*) ; 
 scalar_t__ ixgbevf_reg_test (struct ixgbevf_adapter*,int*) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_diag_test(struct net_device *netdev,
			      struct ethtool_test *eth_test, u64 *data)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	bool if_running = netif_running(netdev);

	if (IXGBE_REMOVED(adapter->hw.hw_addr)) {
		dev_err(&adapter->pdev->dev,
			"Adapter removed - test blocked\n");
		data[0] = 1;
		data[1] = 1;
		eth_test->flags |= ETH_TEST_FL_FAILED;
		return;
	}
	set_bit(__IXGBEVF_TESTING, &adapter->state);
	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */

		hw_dbg(&adapter->hw, "offline testing starting\n");

		/* Link test performed before hardware reset so autoneg doesn't
		 * interfere with test result
		 */
		if (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (if_running)
			/* indicate we're in test mode */
			ixgbevf_close(netdev);
		else
			ixgbevf_reset(adapter);

		hw_dbg(&adapter->hw, "register testing starting\n");
		if (ixgbevf_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		ixgbevf_reset(adapter);

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
		if (if_running)
			ixgbevf_open(netdev);
	} else {
		hw_dbg(&adapter->hw, "online testing starting\n");
		/* Online tests */
		if (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Online tests aren't run; pass by default */
		data[0] = 0;

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
	}
	msleep_interruptible(4 * 1000);
}