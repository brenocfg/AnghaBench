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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int get_link_status; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct igb_adapter {int num_q_vectors; int /*<<< orphan*/  watchdog_task; scalar_t__ vfs_allocated_count; TYPE_1__** q_vector; int /*<<< orphan*/  state; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  netdev; int /*<<< orphan*/  num_tx_queues; struct pci_dev* pdev; struct e1000_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_PFRSTD ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_TSICR ; 
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  __IGB_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_configure (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_rx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_all_tx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_free_irq (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_irq_enable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_power_down_link (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_power_up_link (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_release_hw_control (struct igb_adapter*) ; 
 int igb_request_irq (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset (struct igb_adapter*) ; 
 int igb_setup_all_rx_resources (struct igb_adapter*) ; 
 int igb_setup_all_tx_resources (struct igb_adapter*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __igb_open(struct net_device *netdev, bool resuming)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	int err;
	int i;

	/* disallow open during test */
	if (test_bit(__IGB_TESTING, &adapter->state)) {
		WARN_ON(resuming);
		return -EBUSY;
	}

	if (!resuming)
		pm_runtime_get_sync(&pdev->dev);

	netif_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = igb_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = igb_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	igb_power_up_link(adapter);

	/* before we allocate an interrupt, we must be ready to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an interrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler before we do so.
	 */
	igb_configure(adapter);

	err = igb_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* Notify the stack of the actual queue counts. */
	err = netif_set_real_num_tx_queues(adapter->netdev,
					   adapter->num_tx_queues);
	if (err)
		goto err_set_queues;

	err = netif_set_real_num_rx_queues(adapter->netdev,
					   adapter->num_rx_queues);
	if (err)
		goto err_set_queues;

	/* From here on the code is the same as igb_up() */
	clear_bit(__IGB_DOWN, &adapter->state);

	for (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&(adapter->q_vector[i]->napi));

	/* Clear any pending interrupts. */
	rd32(E1000_TSICR);
	rd32(E1000_ICR);

	igb_irq_enable(adapter);

	/* notify VFs that reset has been completed */
	if (adapter->vfs_allocated_count) {
		u32 reg_data = rd32(E1000_CTRL_EXT);

		reg_data |= E1000_CTRL_EXT_PFRSTD;
		wr32(E1000_CTRL_EXT, reg_data);
	}

	netif_tx_start_all_queues(netdev);

	if (!resuming)
		pm_runtime_put(&pdev->dev);

	/* start the watchdog. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchdog_task);

	return 0;

err_set_queues:
	igb_free_irq(adapter);
err_req_irq:
	igb_release_hw_control(adapter);
	igb_power_down_link(adapter);
	igb_free_all_rx_resources(adapter);
err_setup_rx:
	igb_free_all_tx_resources(adapter);
err_setup_tx:
	igb_reset(adapter);
	if (!resuming)
		pm_runtime_put(&pdev->dev);

	return err;
}