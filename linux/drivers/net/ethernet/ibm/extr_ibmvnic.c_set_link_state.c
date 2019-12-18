#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  link_state; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ logical_link_state; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ibmvnic_adapter {int init_done_rc; int /*<<< orphan*/  init_done; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  LOGICAL_LINK_STATE ; 
 int ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int set_link_state(struct ibmvnic_adapter *adapter, u8 link_state)
{
	struct net_device *netdev = adapter->netdev;
	unsigned long timeout = msecs_to_jiffies(30000);
	union ibmvnic_crq crq;
	bool resend;
	int rc;

	netdev_dbg(netdev, "setting link state %d\n", link_state);

	memset(&crq, 0, sizeof(crq));
	crq.logical_link_state.first = IBMVNIC_CRQ_CMD;
	crq.logical_link_state.cmd = LOGICAL_LINK_STATE;
	crq.logical_link_state.link_state = link_state;

	do {
		resend = false;

		reinit_completion(&adapter->init_done);
		rc = ibmvnic_send_crq(adapter, &crq);
		if (rc) {
			netdev_err(netdev, "Failed to set link state\n");
			return rc;
		}

		if (!wait_for_completion_timeout(&adapter->init_done,
						 timeout)) {
			netdev_err(netdev, "timeout setting link state\n");
			return -1;
		}

		if (adapter->init_done_rc == 1) {
			/* Partuial success, delay and re-send */
			mdelay(1000);
			resend = true;
		} else if (adapter->init_done_rc) {
			netdev_warn(netdev, "Unable to set link state, rc=%d\n",
				    adapter->init_done_rc);
			return adapter->init_done_rc;
		}
	} while (resend);

	return 0;
}