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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int status; } ;
struct TYPE_6__ {TYPE_2__ mng_cookie; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  pm_qos_req; int /*<<< orphan*/  state; int /*<<< orphan*/  mng_vlan_id; TYPE_3__ hw; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  napi; TYPE_1__* netdev; struct pci_dev* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int E1000_CHECK_RESET_COUNT ; 
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int FLAG_HAS_AMT ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  __E1000_TESTING ; 
 int /*<<< orphan*/  e1000_free_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_vlan_rx_kill_vid (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_down (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000e_free_rx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_free_tx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_release_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int e1000e_close(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;
	int count = E1000_CHECK_RESET_COUNT;

	while (test_bit(__E1000_RESETTING, &adapter->state) && count--)
		usleep_range(10000, 11000);

	WARN_ON(test_bit(__E1000_RESETTING, &adapter->state));

	pm_runtime_get_sync(&pdev->dev);

	if (!test_bit(__E1000_DOWN, &adapter->state)) {
		e1000e_down(adapter, true);
		e1000_free_irq(adapter);

		/* Link status message must follow this format */
		pr_info("%s NIC Link is Down\n", adapter->netdev->name);
	}

	napi_disable(&adapter->napi);

	e1000e_free_tx_resources(adapter->tx_ring);
	e1000e_free_rx_resources(adapter->rx_ring);

	/* kill manageability vlan ID if supported, but not if a vlan with
	 * the same ID is registered on the host OS (let 8021q kill it)
	 */
	if (adapter->hw.mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN)
		e1000_vlan_rx_kill_vid(netdev, htons(ETH_P_8021Q),
				       adapter->mng_vlan_id);

	/* If AMT is enabled, let the firmware know that the network
	 * interface is now closed
	 */
	if ((adapter->flags & FLAG_HAS_AMT) &&
	    !test_bit(__E1000_TESTING, &adapter->state))
		e1000e_release_hw_control(adapter);

	pm_qos_remove_request(&adapter->pm_qos_req);

	pm_runtime_put_sync(&pdev->dev);

	return 0;
}