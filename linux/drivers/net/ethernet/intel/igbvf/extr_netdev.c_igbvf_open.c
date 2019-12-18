#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int get_link_status; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igbvf_adapter {int /*<<< orphan*/  tx_ring; TYPE_2__* rx_ring; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; struct e1000_hw hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EICR ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  __IGBVF_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_configure (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_free_rx_resources (TYPE_2__*) ; 
 int /*<<< orphan*/  igbvf_free_tx_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_irq_enable (struct igbvf_adapter*) ; 
 int igbvf_request_irq (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_reset (struct igbvf_adapter*) ; 
 int igbvf_setup_rx_resources (struct igbvf_adapter*,TYPE_2__*) ; 
 int igbvf_setup_tx_resources (struct igbvf_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igbvf_open(struct net_device *netdev)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int err;

	/* disallow open during test */
	if (test_bit(__IGBVF_TESTING, &adapter->state))
		return -EBUSY;

	/* allocate transmit descriptors */
	err = igbvf_setup_tx_resources(adapter, adapter->tx_ring);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = igbvf_setup_rx_resources(adapter, adapter->rx_ring);
	if (err)
		goto err_setup_rx;

	/* before we allocate an interrupt, we must be ready to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an interrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler before we do so.
	 */
	igbvf_configure(adapter);

	err = igbvf_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* From here on the code is the same as igbvf_up() */
	clear_bit(__IGBVF_DOWN, &adapter->state);

	napi_enable(&adapter->rx_ring->napi);

	/* clear any pending interrupts */
	er32(EICR);

	igbvf_irq_enable(adapter);

	/* start the watchdog */
	hw->mac.get_link_status = 1;
	mod_timer(&adapter->watchdog_timer, jiffies + 1);

	return 0;

err_req_irq:
	igbvf_free_rx_resources(adapter->rx_ring);
err_setup_rx:
	igbvf_free_tx_resources(adapter->tx_ring);
err_setup_tx:
	igbvf_reset(adapter);

	return err;
}