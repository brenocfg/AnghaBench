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
struct ibmvnic_adapter {scalar_t__ state; struct net_device* netdev; int /*<<< orphan*/  init_done; int /*<<< orphan*/  reset_reason; } ;

/* Variables and functions */
 int IBMVNIC_OPEN_FAILED ; 
 scalar_t__ VNIC_CLOSED ; 
 scalar_t__ VNIC_PROBED ; 
 int __ibmvnic_open (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_disable_irqs (struct ibmvnic_adapter*) ; 
 int ibmvnic_init (struct ibmvnic_adapter*) ; 
 int ibmvnic_login (struct net_device*) ; 
 int init_crq_queue (struct ibmvnic_adapter*) ; 
 int init_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_hard_reset(struct ibmvnic_adapter *adapter,
			 struct ibmvnic_rwi *rwi, u32 reset_state)
{
	struct net_device *netdev = adapter->netdev;
	int rc;

	netdev_dbg(adapter->netdev, "Hard resetting driver (%d)\n",
		   rwi->reset_reason);

	netif_carrier_off(netdev);
	adapter->reset_reason = rwi->reset_reason;

	ibmvnic_cleanup(netdev);
	release_resources(adapter);
	release_sub_crqs(adapter, 0);
	release_crq_queue(adapter);

	/* remove the closed state so when we call open it appears
	 * we are coming from the probed state.
	 */
	adapter->state = VNIC_PROBED;

	reinit_completion(&adapter->init_done);
	rc = init_crq_queue(adapter);
	if (rc) {
		netdev_err(adapter->netdev,
			   "Couldn't initialize crq. rc=%d\n", rc);
		return rc;
	}

	rc = ibmvnic_init(adapter);
	if (rc)
		return rc;

	/* If the adapter was in PROBE state prior to the reset,
	 * exit here.
	 */
	if (reset_state == VNIC_PROBED)
		return 0;

	rc = ibmvnic_login(netdev);
	if (rc) {
		adapter->state = VNIC_PROBED;
		return 0;
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

	return 0;
}