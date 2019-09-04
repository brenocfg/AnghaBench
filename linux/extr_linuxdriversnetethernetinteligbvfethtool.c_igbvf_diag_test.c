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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct igbvf_adapter {int /*<<< orphan*/  state; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  __IGBVF_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ igbvf_link_test (struct igbvf_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igbvf_diag_test(struct net_device *netdev,
			    struct ethtool_test *eth_test, u64 *data)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	set_bit(__IGBVF_TESTING, &adapter->state);

	/* Link test performed before hardware reset so autoneg doesn't
	 * interfere with test result
	 */
	if (igbvf_link_test(adapter, &data[0]))
		eth_test->flags |= ETH_TEST_FL_FAILED;

	clear_bit(__IGBVF_TESTING, &adapter->state);
	msleep_interruptible(4 * 1000);
}