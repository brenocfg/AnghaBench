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
struct net_device {int dummy; } ;
struct TYPE_4__ {int get_link_status; } ;
struct igc_hw {TYPE_2__ mac; } ;
struct igc_adapter {int num_q_vectors; int /*<<< orphan*/  watchdog_task; TYPE_1__** q_vector; int /*<<< orphan*/  state; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  num_tx_queues; struct igc_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IGC_ICR ; 
 int IGC_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __IGC_DOWN ; 
 int /*<<< orphan*/  __IGC_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igc_configure (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_rx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_all_tx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_free_irq (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_irq_enable (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_power_down_link (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_power_up_link (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_release_hw_control (struct igc_adapter*) ; 
 int igc_request_irq (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset (struct igc_adapter*) ; 
 int igc_setup_all_rx_resources (struct igc_adapter*) ; 
 int igc_setup_all_tx_resources (struct igc_adapter*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __igc_open(struct net_device *netdev, bool resuming)
{
	struct igc_adapter *adapter = netdev_priv(netdev);
	struct igc_hw *hw = &adapter->hw;
	int err = 0;
	int i = 0;

	/* disallow open during test */

	if (test_bit(__IGC_TESTING, &adapter->state)) {
		WARN_ON(resuming);
		return -EBUSY;
	}

	netif_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = igc_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = igc_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	igc_power_up_link(adapter);

	igc_configure(adapter);

	err = igc_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* Notify the stack of the actual queue counts. */
	err = netif_set_real_num_tx_queues(netdev, adapter->num_tx_queues);
	if (err)
		goto err_set_queues;

	err = netif_set_real_num_rx_queues(netdev, adapter->num_rx_queues);
	if (err)
		goto err_set_queues;

	clear_bit(__IGC_DOWN, &adapter->state);

	for (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&adapter->q_vector[i]->napi);

	/* Clear any pending interrupts. */
	rd32(IGC_ICR);
	igc_irq_enable(adapter);

	netif_tx_start_all_queues(netdev);

	/* start the watchdog. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchdog_task);

	return IGC_SUCCESS;

err_set_queues:
	igc_free_irq(adapter);
err_req_irq:
	igc_release_hw_control(adapter);
	igc_power_down_link(adapter);
	igc_free_all_rx_resources(adapter);
err_setup_rx:
	igc_free_all_tx_resources(adapter);
err_setup_tx:
	igc_reset(adapter);

	return err;
}