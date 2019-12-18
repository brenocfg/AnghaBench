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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ibmvnic_rwi {int /*<<< orphan*/  reset_reason; } ;
struct ibmvnic_adapter {int req_rx_queues; int /*<<< orphan*/ * napi; scalar_t__ state; struct net_device* netdev; int /*<<< orphan*/  reset_reason; } ;

/* Variables and functions */
 int IBMVNIC_INIT_FAILED ; 
 int IBMVNIC_OPEN_FAILED ; 
 scalar_t__ VNIC_CLOSED ; 
 scalar_t__ VNIC_OPEN ; 
 scalar_t__ VNIC_PROBED ; 
 int __ibmvnic_close (struct net_device*) ; 
 int __ibmvnic_open (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_disable_irqs (struct ibmvnic_adapter*) ; 
 int ibmvnic_login (struct net_device*) ; 
 int ibmvnic_reset_init (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  ibmvnic_set_multi (struct net_device*) ; 
 int init_crq_queue (struct ibmvnic_adapter*) ; 
 int init_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int) ; 

__attribute__((used)) static int do_change_param_reset(struct ibmvnic_adapter *adapter,
				 struct ibmvnic_rwi *rwi,
				 u32 reset_state)
{
	struct net_device *netdev = adapter->netdev;
	int i, rc;

	netdev_dbg(adapter->netdev, "Change param resetting driver (%d)\n",
		   rwi->reset_reason);

	netif_carrier_off(netdev);
	adapter->reset_reason = rwi->reset_reason;

	ibmvnic_cleanup(netdev);

	if (reset_state == VNIC_OPEN) {
		rc = __ibmvnic_close(netdev);
		if (rc)
			return rc;
	}

	release_resources(adapter);
	release_sub_crqs(adapter, 1);
	release_crq_queue(adapter);

	adapter->state = VNIC_PROBED;

	rc = init_crq_queue(adapter);

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

	rc = init_resources(adapter);
	if (rc)
		return rc;

	ibmvnic_disable_irqs(adapter);

	adapter->state = VNIC_CLOSED;

	if (reset_state == VNIC_CLOSED)
		return 0;

	rc = __ibmvnic_open(netdev);
	if (rc)
		return IBMVNIC_OPEN_FAILED;

	/* refresh device's multicast list */
	ibmvnic_set_multi(netdev);

	/* kick napi */
	for (i = 0; i < adapter->req_rx_queues; i++)
		napi_schedule(&adapter->napi[i]);

	return 0;
}