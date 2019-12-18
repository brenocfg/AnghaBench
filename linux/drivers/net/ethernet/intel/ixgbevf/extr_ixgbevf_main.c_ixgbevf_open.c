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
struct ixgbe_hw {scalar_t__ adapter_stopped; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  state; int /*<<< orphan*/  num_msix_vectors; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  __IXGBEVF_TESTING ; 
 int /*<<< orphan*/  ixgbevf_configure (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_free_all_rx_resources (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_free_all_tx_resources (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_free_irq (struct ixgbevf_adapter*) ; 
 int ixgbevf_request_irq (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int ixgbevf_setup_all_rx_resources (struct ixgbevf_adapter*) ; 
 int ixgbevf_setup_all_tx_resources (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_up_complete (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ixgbevf_open(struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	int err;

	/* A previous failure to open the device because of a lack of
	 * available MSIX vector resources may have reset the number
	 * of msix vectors variable to zero.  The only way to recover
	 * is to unload/reload the driver and hope that the system has
	 * been able to recover some MSIX vector resources.
	 */
	if (!adapter->num_msix_vectors)
		return -ENOMEM;

	if (hw->adapter_stopped) {
		ixgbevf_reset(adapter);
		/* if adapter is still stopped then PF isn't up and
		 * the VF can't start.
		 */
		if (hw->adapter_stopped) {
			err = IXGBE_ERR_MBX;
			pr_err("Unable to start - perhaps the PF Driver isn't up yet\n");
			goto err_setup_reset;
		}
	}

	/* disallow open during test */
	if (test_bit(__IXGBEVF_TESTING, &adapter->state))
		return -EBUSY;

	netif_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = ixgbevf_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = ixgbevf_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	ixgbevf_configure(adapter);

	err = ixgbevf_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* Notify the stack of the actual queue counts. */
	err = netif_set_real_num_tx_queues(netdev, adapter->num_tx_queues);
	if (err)
		goto err_set_queues;

	err = netif_set_real_num_rx_queues(netdev, adapter->num_rx_queues);
	if (err)
		goto err_set_queues;

	ixgbevf_up_complete(adapter);

	return 0;

err_set_queues:
	ixgbevf_free_irq(adapter);
err_req_irq:
	ixgbevf_free_all_rx_resources(adapter);
err_setup_rx:
	ixgbevf_free_all_tx_resources(adapter);
err_setup_tx:
	ixgbevf_reset(adapter);
err_setup_reset:

	return err;
}