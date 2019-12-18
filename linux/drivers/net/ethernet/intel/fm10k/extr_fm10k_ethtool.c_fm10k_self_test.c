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
struct fm10k_hw {int /*<<< orphan*/  hw_addr; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 scalar_t__ FM10K_REMOVED (int /*<<< orphan*/ ) ; 
 int FM10K_TEST_LEN ; 
 size_t FM10K_TEST_MBX ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ fm10k_mbx_test (struct fm10k_intfc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static void fm10k_self_test(struct net_device *dev,
			    struct ethtool_test *eth_test, u64 *data)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_hw *hw = &interface->hw;

	memset(data, 0, sizeof(*data) * FM10K_TEST_LEN);

	if (FM10K_REMOVED(hw->hw_addr)) {
		netif_err(interface, drv, dev,
			  "Interface removed - test blocked\n");
		eth_test->flags |= ETH_TEST_FL_FAILED;
		return;
	}

	if (fm10k_mbx_test(interface, &data[FM10K_TEST_MBX]))
		eth_test->flags |= ETH_TEST_FL_FAILED;
}