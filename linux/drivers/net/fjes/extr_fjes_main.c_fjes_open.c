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
struct net_device {int dummy; } ;
struct fjes_hw {scalar_t__ epstop_req_bit; scalar_t__ txrx_stop_req_bit; } ;
struct fjes_adapter {int /*<<< orphan*/  napi; scalar_t__ open_guard; struct fjes_hw hw; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  REG_ICTL_MASK_ALL ; 
 int /*<<< orphan*/  fjes_free_irq (struct fjes_adapter*) ; 
 int /*<<< orphan*/  fjes_free_resources (struct fjes_adapter*) ; 
 int /*<<< orphan*/  fjes_hw_capture_interrupt_status (struct fjes_hw*) ; 
 int /*<<< orphan*/  fjes_hw_set_irqmask (struct fjes_hw*,int /*<<< orphan*/ ,int) ; 
 int fjes_request_irq (struct fjes_adapter*) ; 
 int fjes_setup_resources (struct fjes_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 

__attribute__((used)) static int fjes_open(struct net_device *netdev)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;
	int result;

	if (adapter->open_guard)
		return -ENXIO;

	result = fjes_setup_resources(adapter);
	if (result)
		goto err_setup_res;

	hw->txrx_stop_req_bit = 0;
	hw->epstop_req_bit = 0;

	napi_enable(&adapter->napi);

	fjes_hw_capture_interrupt_status(hw);

	result = fjes_request_irq(adapter);
	if (result)
		goto err_req_irq;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, false);

	netif_tx_start_all_queues(netdev);
	netif_carrier_on(netdev);

	return 0;

err_req_irq:
	fjes_free_irq(adapter);
	napi_disable(&adapter->napi);

err_setup_res:
	fjes_free_resources(adapter);
	return result;
}