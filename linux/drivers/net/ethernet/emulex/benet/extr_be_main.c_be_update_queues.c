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
struct be_adapter {int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_handle; int /*<<< orphan*/  num_msix_roce_vec; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_IF_FLAGS_ALL_PROMISCUOUS ; 
 int /*<<< orphan*/  be_cancel_worker (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_close (struct net_device*) ; 
 int be_cmd_if_destroy (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_if_create (struct be_adapter*) ; 
 int /*<<< orphan*/  be_msix_disable (struct be_adapter*) ; 
 int be_msix_enable (struct be_adapter*) ; 
 int be_open (struct net_device*) ; 
 int /*<<< orphan*/  be_schedule_worker (struct be_adapter*) ; 
 int be_setup_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  msix_enabled (struct be_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 

int be_update_queues(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int status;

	if (netif_running(netdev)) {
		/* be_tx_timeout() must not run concurrently with this
		 * function, synchronize with an already-running dev_watchdog
		 */
		netif_tx_lock_bh(netdev);
		/* device cannot transmit now, avoid dev_watchdog timeouts */
		netif_carrier_off(netdev);
		netif_tx_unlock_bh(netdev);

		be_close(netdev);
	}

	be_cancel_worker(adapter);

	/* If any vectors have been shared with RoCE we cannot re-program
	 * the MSIx table.
	 */
	if (!adapter->num_msix_roce_vec)
		be_msix_disable(adapter);

	be_clear_queues(adapter);
	status = be_cmd_if_destroy(adapter, adapter->if_handle,  0);
	if (status)
		return status;

	if (!msix_enabled(adapter)) {
		status = be_msix_enable(adapter);
		if (status)
			return status;
	}

	status = be_if_create(adapter);
	if (status)
		return status;

	status = be_setup_queues(adapter);
	if (status)
		return status;

	be_schedule_worker(adapter);

	/* The IF was destroyed and re-created. We need to clear
	 * all promiscuous flags valid for the destroyed IF.
	 * Without this promisc mode is not restored during
	 * be_open() because the driver thinks that it is
	 * already enabled in HW.
	 */
	adapter->if_flags &= ~BE_IF_FLAGS_ALL_PROMISCUOUS;

	if (netif_running(netdev))
		status = be_open(netdev);

	return status;
}