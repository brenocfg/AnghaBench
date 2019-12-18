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
struct TYPE_4__ {int /*<<< orphan*/  tx_entries; int /*<<< orphan*/  rx_entries; int /*<<< orphan*/  tx_queues; int /*<<< orphan*/  rx_queues; int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_entries; int /*<<< orphan*/  rx_entries; int /*<<< orphan*/  tx_queues; int /*<<< orphan*/  rx_queues; int /*<<< orphan*/  mtu; } ;
struct ibmvnic_adapter {int wait_for_reset; int /*<<< orphan*/  reset_done; TYPE_2__ fallback; TYPE_1__ desired; scalar_t__ reset_done_rc; int /*<<< orphan*/  req_tx_entries_per_subcrq; int /*<<< orphan*/  req_rx_add_entries_per_subcrq; int /*<<< orphan*/  req_tx_queues; int /*<<< orphan*/  req_rx_queues; int /*<<< orphan*/  req_mtu; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VNIC_RESET_CHANGE_PARAM ; 
 int ibmvnic_reset (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_for_reset(struct ibmvnic_adapter *adapter)
{
	int rc, ret;

	adapter->fallback.mtu = adapter->req_mtu;
	adapter->fallback.rx_queues = adapter->req_rx_queues;
	adapter->fallback.tx_queues = adapter->req_tx_queues;
	adapter->fallback.rx_entries = adapter->req_rx_add_entries_per_subcrq;
	adapter->fallback.tx_entries = adapter->req_tx_entries_per_subcrq;

	init_completion(&adapter->reset_done);
	adapter->wait_for_reset = true;
	rc = ibmvnic_reset(adapter, VNIC_RESET_CHANGE_PARAM);
	if (rc)
		return rc;
	wait_for_completion(&adapter->reset_done);

	ret = 0;
	if (adapter->reset_done_rc) {
		ret = -EIO;
		adapter->desired.mtu = adapter->fallback.mtu;
		adapter->desired.rx_queues = adapter->fallback.rx_queues;
		adapter->desired.tx_queues = adapter->fallback.tx_queues;
		adapter->desired.rx_entries = adapter->fallback.rx_entries;
		adapter->desired.tx_entries = adapter->fallback.tx_entries;

		init_completion(&adapter->reset_done);
		adapter->wait_for_reset = true;
		rc = ibmvnic_reset(adapter, VNIC_RESET_CHANGE_PARAM);
		if (rc)
			return ret;
		wait_for_completion(&adapter->reset_done);
	}
	adapter->wait_for_reset = false;

	return ret;
}