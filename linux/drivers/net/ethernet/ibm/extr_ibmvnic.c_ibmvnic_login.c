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
struct ibmvnic_adapter {scalar_t__ init_done_rc; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  init_done; } ;

/* Variables and functions */
 int IBMVNIC_MAX_QUEUES ; 
 scalar_t__ PARTIALSUCCESS ; 
 int /*<<< orphan*/  __ibmvnic_set_mac (struct net_device*,int /*<<< orphan*/ ) ; 
 int init_sub_crq_irqs (struct ibmvnic_adapter*) ; 
 int init_sub_crqs (struct ibmvnic_adapter*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int) ; 
 int /*<<< orphan*/  send_cap_queries (struct ibmvnic_adapter*) ; 
 int send_login (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ibmvnic_login(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	unsigned long timeout = msecs_to_jiffies(30000);
	int retry_count = 0;
	bool retry;
	int rc;

	do {
		retry = false;
		if (retry_count > IBMVNIC_MAX_QUEUES) {
			netdev_warn(netdev, "Login attempts exceeded\n");
			return -1;
		}

		adapter->init_done_rc = 0;
		reinit_completion(&adapter->init_done);
		rc = send_login(adapter);
		if (rc) {
			netdev_warn(netdev, "Unable to login\n");
			return rc;
		}

		if (!wait_for_completion_timeout(&adapter->init_done,
						 timeout)) {
			netdev_warn(netdev, "Login timed out\n");
			return -1;
		}

		if (adapter->init_done_rc == PARTIALSUCCESS) {
			retry_count++;
			release_sub_crqs(adapter, 1);

			retry = true;
			netdev_dbg(netdev,
				   "Received partial success, retrying...\n");
			adapter->init_done_rc = 0;
			reinit_completion(&adapter->init_done);
			send_cap_queries(adapter);
			if (!wait_for_completion_timeout(&adapter->init_done,
							 timeout)) {
				netdev_warn(netdev,
					    "Capabilities query timed out\n");
				return -1;
			}

			rc = init_sub_crqs(adapter);
			if (rc) {
				netdev_warn(netdev,
					    "SCRQ initialization failed\n");
				return -1;
			}

			rc = init_sub_crq_irqs(adapter);
			if (rc) {
				netdev_warn(netdev,
					    "SCRQ irq initialization failed\n");
				return -1;
			}
		} else if (adapter->init_done_rc) {
			netdev_warn(netdev, "Adapter login failed\n");
			return -1;
		}
	} while (retry);

	__ibmvnic_set_mac(netdev, adapter->mac_addr);

	return 0;
}