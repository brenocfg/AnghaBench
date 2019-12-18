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
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct hns_nic_priv {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; TYPE_1__* ae_handle; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
typedef  enum hnae_loop { ____Placeholder_hnae_loop } hnae_loop ;
struct TYPE_2__ {scalar_t__ phy_if; int /*<<< orphan*/  phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 int MAC_INTERNALLOOP_MAC ; 
 int MAC_INTERNALLOOP_PHY ; 
 int MAC_INTERNALLOOP_SERDES ; 
 int /*<<< orphan*/  NIC_STATE_TESTING ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int SELF_TEST_TPYE_NUM ; 
 int /*<<< orphan*/  __lb_down (struct net_device*,int) ; 
 scalar_t__ __lb_run_test (struct net_device*,int) ; 
 scalar_t__ __lb_up (struct net_device*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_nic_net_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_nic_self_test(struct net_device *ndev,
			      struct ethtool_test *eth_test, u64 *data)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	bool if_running = netif_running(ndev);
#define SELF_TEST_TPYE_NUM 3
	int st_param[SELF_TEST_TPYE_NUM][2];
	int i;
	int test_index = 0;

	st_param[0][0] = MAC_INTERNALLOOP_MAC; /* XGE not supported lb */
	st_param[0][1] = (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII);
	st_param[1][0] = MAC_INTERNALLOOP_SERDES;
	st_param[1][1] = 1; /*serdes must exist*/
	st_param[2][0] = MAC_INTERNALLOOP_PHY; /* only supporte phy node*/
	st_param[2][1] = ((!!(priv->ae_handle->phy_dev)) &&
		(priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII));

	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		set_bit(NIC_STATE_TESTING, &priv->state);

		if (if_running)
			dev_close(ndev);

		for (i = 0; i < SELF_TEST_TPYE_NUM; i++) {
			if (!st_param[i][1])
				continue;	/* NEXT testing */

			data[test_index] = __lb_up(ndev,
				(enum hnae_loop)st_param[i][0]);
			if (!data[test_index]) {
				data[test_index] = __lb_run_test(
					ndev, (enum hnae_loop)st_param[i][0]);
				(void)__lb_down(ndev,
						(enum hnae_loop)st_param[i][0]);
			}

			if (data[test_index])
				eth_test->flags |= ETH_TEST_FL_FAILED;

			test_index++;
		}

		hns_nic_net_reset(priv->netdev);

		clear_bit(NIC_STATE_TESTING, &priv->state);

		if (if_running)
			(void)dev_open(ndev, NULL);
	}
	/* Online tests aren't run; pass by default */

	(void)msleep_interruptible(4 * 1000);
}