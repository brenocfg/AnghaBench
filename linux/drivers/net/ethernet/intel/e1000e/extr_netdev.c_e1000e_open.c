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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int get_link_status; } ;
struct TYPE_3__ {int status; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ mng_cookie; } ;
struct e1000_adapter {int flags; scalar_t__ int_mode; int tx_hang_recheck; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  pm_qos_req; int /*<<< orphan*/  napi; int /*<<< orphan*/  state; struct e1000_hw hw; int /*<<< orphan*/  mng_vlan_id; struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ E1000E_INT_MODE_LEGACY ; 
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN ; 
 int /*<<< orphan*/  E1000_MNG_VLAN_NONE ; 
 int EBUSY ; 
 int FLAG_HAS_AMT ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __E1000_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_configure (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_power_down_phy (struct e1000_adapter*) ; 
 int e1000_request_irq (struct e1000_adapter*) ; 
 int e1000_test_msi (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_update_mng_vlan (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_free_rx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_free_tx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_get_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_power_up_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_release_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int e1000e_setup_rx_resources (int /*<<< orphan*/ ) ; 
 int e1000e_setup_tx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_trigger_lsc (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int e1000e_open(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	int err;

	/* disallow open during test */
	if (test_bit(__E1000_TESTING, &adapter->state))
		return -EBUSY;

	pm_runtime_get_sync(&pdev->dev);

	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	/* allocate transmit descriptors */
	err = e1000e_setup_tx_resources(adapter->tx_ring);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = e1000e_setup_rx_resources(adapter->rx_ring);
	if (err)
		goto err_setup_rx;

	/* If AMT is enabled, let the firmware know that the network
	 * interface is now open and reset the part to a known state.
	 */
	if (adapter->flags & FLAG_HAS_AMT) {
		e1000e_get_hw_control(adapter);
		e1000e_reset(adapter);
	}

	e1000e_power_up_phy(adapter);

	adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
	if ((adapter->hw.mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN))
		e1000_update_mng_vlan(adapter);

	/* DMA latency requirement to workaround jumbo issue */
	pm_qos_add_request(&adapter->pm_qos_req, PM_QOS_CPU_DMA_LATENCY,
			   PM_QOS_DEFAULT_VALUE);

	/* before we allocate an interrupt, we must be ready to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an interrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler before we do so.
	 */
	e1000_configure(adapter);

	err = e1000_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* Work around PCIe errata with MSI interrupts causing some chipsets to
	 * ignore e1000e MSI messages, which means we need to test our MSI
	 * interrupt now
	 */
	if (adapter->int_mode != E1000E_INT_MODE_LEGACY) {
		err = e1000_test_msi(adapter);
		if (err) {
			e_err("Interrupt allocation failed\n");
			goto err_req_irq;
		}
	}

	/* From here on the code is the same as e1000e_up() */
	clear_bit(__E1000_DOWN, &adapter->state);

	napi_enable(&adapter->napi);

	e1000_irq_enable(adapter);

	adapter->tx_hang_recheck = false;

	hw->mac.get_link_status = true;
	pm_runtime_put(&pdev->dev);

	e1000e_trigger_lsc(adapter);

	return 0;

err_req_irq:
	pm_qos_remove_request(&adapter->pm_qos_req);
	e1000e_release_hw_control(adapter);
	e1000_power_down_phy(adapter);
	e1000e_free_rx_resources(adapter->rx_ring);
err_setup_rx:
	e1000e_free_tx_resources(adapter->tx_ring);
err_setup_tx:
	e1000e_reset(adapter);
	pm_runtime_put_sync(&pdev->dev);

	return err;
}