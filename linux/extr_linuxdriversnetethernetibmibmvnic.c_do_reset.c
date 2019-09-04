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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ibmvnic_rwi {scalar_t__ reset_reason; } ;
struct ibmvnic_adapter {scalar_t__ reset_reason; scalar_t__ req_rx_queues; scalar_t__ req_tx_queues; scalar_t__ req_rx_add_entries_per_subcrq; scalar_t__ req_tx_entries_per_subcrq; int /*<<< orphan*/ * napi; scalar_t__ state; int /*<<< orphan*/  rwi_list; scalar_t__ wait_for_reset; struct net_device* netdev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int IBMVNIC_INIT_FAILED ; 
 scalar_t__ VNIC_CLOSED ; 
 scalar_t__ VNIC_PROBED ; 
 scalar_t__ VNIC_RESET_CHANGE_PARAM ; 
 scalar_t__ VNIC_RESET_FAILOVER ; 
 scalar_t__ VNIC_RESET_MOBILITY ; 
 scalar_t__ VNIC_RESET_NON_FATAL ; 
 int __ibmvnic_close (struct net_device*) ; 
 int __ibmvnic_open (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_disable_irqs (struct ibmvnic_adapter*) ; 
 int ibmvnic_login (struct net_device*) ; 
 int ibmvnic_reenable_crq_queue (struct ibmvnic_adapter*) ; 
 int ibmvnic_reset_crq (struct ibmvnic_adapter*) ; 
 int ibmvnic_reset_init (struct ibmvnic_adapter*) ; 
 int init_crq_queue (struct ibmvnic_adapter*) ; 
 int init_resources (struct ibmvnic_adapter*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_notify_peers (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_napi (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_rx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int) ; 
 int /*<<< orphan*/  release_tx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_vpd_data (struct ibmvnic_adapter*) ; 
 int reset_rx_pools (struct ibmvnic_adapter*) ; 
 int reset_tx_pools (struct ibmvnic_adapter*) ; 
 int vio_enable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_reset(struct ibmvnic_adapter *adapter,
		    struct ibmvnic_rwi *rwi, u32 reset_state)
{
	u64 old_num_rx_queues, old_num_tx_queues;
	u64 old_num_rx_slots, old_num_tx_slots;
	struct net_device *netdev = adapter->netdev;
	int i, rc;

	netdev_dbg(adapter->netdev, "Re-setting driver (%d)\n",
		   rwi->reset_reason);

	netif_carrier_off(netdev);
	adapter->reset_reason = rwi->reset_reason;

	old_num_rx_queues = adapter->req_rx_queues;
	old_num_tx_queues = adapter->req_tx_queues;
	old_num_rx_slots = adapter->req_rx_add_entries_per_subcrq;
	old_num_tx_slots = adapter->req_tx_entries_per_subcrq;

	ibmvnic_cleanup(netdev);

	if (adapter->reset_reason != VNIC_RESET_MOBILITY &&
	    adapter->reset_reason != VNIC_RESET_FAILOVER) {
		rc = __ibmvnic_close(netdev);
		if (rc)
			return rc;
	}

	if (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM ||
	    adapter->wait_for_reset) {
		release_resources(adapter);
		release_sub_crqs(adapter, 1);
		release_crq_queue(adapter);
	}

	if (adapter->reset_reason != VNIC_RESET_NON_FATAL) {
		/* remove the closed state so when we call open it appears
		 * we are coming from the probed state.
		 */
		adapter->state = VNIC_PROBED;

		if (adapter->wait_for_reset) {
			rc = init_crq_queue(adapter);
		} else if (adapter->reset_reason == VNIC_RESET_MOBILITY) {
			rc = ibmvnic_reenable_crq_queue(adapter);
			release_sub_crqs(adapter, 1);
		} else {
			rc = ibmvnic_reset_crq(adapter);
			if (!rc)
				rc = vio_enable_interrupts(adapter->vdev);
		}

		if (rc) {
			netdev_err(adapter->netdev,
				   "Couldn't initialize crq. rc=%d\n", rc);
			return rc;
		}

		rc = ibmvnic_reset_init(adapter);
		if (rc)
			return IBMVNIC_INIT_FAILED;

		/* If the adapter was in PROBE state prior to the reset,
		 * exit here.
		 */
		if (reset_state == VNIC_PROBED)
			return 0;

		rc = ibmvnic_login(netdev);
		if (rc) {
			adapter->state = reset_state;
			return rc;
		}

		if (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM ||
		    adapter->wait_for_reset) {
			rc = init_resources(adapter);
			if (rc)
				return rc;
		} else if (adapter->req_rx_queues != old_num_rx_queues ||
			   adapter->req_tx_queues != old_num_tx_queues ||
			   adapter->req_rx_add_entries_per_subcrq !=
							old_num_rx_slots ||
			   adapter->req_tx_entries_per_subcrq !=
							old_num_tx_slots) {
			release_rx_pools(adapter);
			release_tx_pools(adapter);
			release_napi(adapter);
			release_vpd_data(adapter);

			rc = init_resources(adapter);
			if (rc)
				return rc;

		} else {
			rc = reset_tx_pools(adapter);
			if (rc)
				return rc;

			rc = reset_rx_pools(adapter);
			if (rc)
				return rc;
		}
		ibmvnic_disable_irqs(adapter);
	}
	adapter->state = VNIC_CLOSED;

	if (reset_state == VNIC_CLOSED)
		return 0;

	rc = __ibmvnic_open(netdev);
	if (rc) {
		if (list_empty(&adapter->rwi_list))
			adapter->state = VNIC_CLOSED;
		else
			adapter->state = reset_state;

		return 0;
	}

	/* kick napi */
	for (i = 0; i < adapter->req_rx_queues; i++)
		napi_schedule(&adapter->napi[i]);

	if (adapter->reset_reason != VNIC_RESET_FAILOVER &&
	    adapter->reset_reason != VNIC_RESET_CHANGE_PARAM)
		netdev_notify_peers(netdev);

	netif_carrier_on(netdev);

	return 0;
}