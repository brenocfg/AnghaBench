#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* number; void* capability; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_4__ request_capability; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int mtu; int tx_entries; int rx_entries; int tx_queues; int rx_queues; } ;
struct ibmvnic_adapter {int min_tx_entries_per_subcrq; int min_rx_add_entries_per_subcrq; int req_mtu; int max_tx_entries_per_subcrq; int max_rx_add_entries_per_subcrq; int req_tx_entries_per_subcrq; int req_rx_add_entries_per_subcrq; int req_tx_queues; int opt_tx_comp_sub_queues; int req_rx_queues; int opt_rx_comp_queues; int req_rx_add_queues; int max_rx_add_queues; int /*<<< orphan*/  running_cap_crqs; scalar_t__ promisc_supported; TYPE_2__* netdev; TYPE_3__ desired; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  crq ;
struct TYPE_6__ {int mtu; int flags; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int IBMVNIC_BUFFER_HLEN ; 
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int IBMVNIC_MAX_LTB_SIZE ; 
 int IFF_PROMISC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PROMISC_REQUESTED ; 
 int /*<<< orphan*/  REQUEST_CAPABILITY ; 
 int /*<<< orphan*/  REQ_MTU ; 
 int /*<<< orphan*/  REQ_RX_ADD_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  REQ_RX_ADD_QUEUES ; 
 int /*<<< orphan*/  REQ_RX_QUEUES ; 
 int /*<<< orphan*/  REQ_TX_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  REQ_TX_QUEUES ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ibmvnic_send_req_caps(struct ibmvnic_adapter *adapter, int retry)
{
	struct device *dev = &adapter->vdev->dev;
	union ibmvnic_crq crq;
	int max_entries;

	if (!retry) {
		/* Sub-CRQ entries are 32 byte long */
		int entries_page = 4 * PAGE_SIZE / (sizeof(u64) * 4);

		if (adapter->min_tx_entries_per_subcrq > entries_page ||
		    adapter->min_rx_add_entries_per_subcrq > entries_page) {
			dev_err(dev, "Fatal, invalid entries per sub-crq\n");
			return;
		}

		if (adapter->desired.mtu)
			adapter->req_mtu = adapter->desired.mtu;
		else
			adapter->req_mtu = adapter->netdev->mtu + ETH_HLEN;

		if (!adapter->desired.tx_entries)
			adapter->desired.tx_entries =
					adapter->max_tx_entries_per_subcrq;
		if (!adapter->desired.rx_entries)
			adapter->desired.rx_entries =
					adapter->max_rx_add_entries_per_subcrq;

		max_entries = IBMVNIC_MAX_LTB_SIZE /
			      (adapter->req_mtu + IBMVNIC_BUFFER_HLEN);

		if ((adapter->req_mtu + IBMVNIC_BUFFER_HLEN) *
			adapter->desired.tx_entries > IBMVNIC_MAX_LTB_SIZE) {
			adapter->desired.tx_entries = max_entries;
		}

		if ((adapter->req_mtu + IBMVNIC_BUFFER_HLEN) *
			adapter->desired.rx_entries > IBMVNIC_MAX_LTB_SIZE) {
			adapter->desired.rx_entries = max_entries;
		}

		if (adapter->desired.tx_entries)
			adapter->req_tx_entries_per_subcrq =
					adapter->desired.tx_entries;
		else
			adapter->req_tx_entries_per_subcrq =
					adapter->max_tx_entries_per_subcrq;

		if (adapter->desired.rx_entries)
			adapter->req_rx_add_entries_per_subcrq =
					adapter->desired.rx_entries;
		else
			adapter->req_rx_add_entries_per_subcrq =
					adapter->max_rx_add_entries_per_subcrq;

		if (adapter->desired.tx_queues)
			adapter->req_tx_queues =
					adapter->desired.tx_queues;
		else
			adapter->req_tx_queues =
					adapter->opt_tx_comp_sub_queues;

		if (adapter->desired.rx_queues)
			adapter->req_rx_queues =
					adapter->desired.rx_queues;
		else
			adapter->req_rx_queues =
					adapter->opt_rx_comp_queues;

		adapter->req_rx_add_queues = adapter->max_rx_add_queues;
	}

	memset(&crq, 0, sizeof(crq));
	crq.request_capability.first = IBMVNIC_CRQ_CMD;
	crq.request_capability.cmd = REQUEST_CAPABILITY;

	crq.request_capability.capability = cpu_to_be16(REQ_TX_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_tx_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_RX_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_rx_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_RX_ADD_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_rx_add_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability =
	    cpu_to_be16(REQ_TX_ENTRIES_PER_SUBCRQ);
	crq.request_capability.number =
	    cpu_to_be64(adapter->req_tx_entries_per_subcrq);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability =
	    cpu_to_be16(REQ_RX_ADD_ENTRIES_PER_SUBCRQ);
	crq.request_capability.number =
	    cpu_to_be64(adapter->req_rx_add_entries_per_subcrq);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_MTU);
	crq.request_capability.number = cpu_to_be64(adapter->req_mtu);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	if (adapter->netdev->flags & IFF_PROMISC) {
		if (adapter->promisc_supported) {
			crq.request_capability.capability =
			    cpu_to_be16(PROMISC_REQUESTED);
			crq.request_capability.number = cpu_to_be64(1);
			atomic_inc(&adapter->running_cap_crqs);
			ibmvnic_send_crq(adapter, &crq);
		}
	} else {
		crq.request_capability.capability =
		    cpu_to_be16(PROMISC_REQUESTED);
		crq.request_capability.number = cpu_to_be64(0);
		atomic_inc(&adapter->running_cap_crqs);
		ibmvnic_send_crq(adapter, &crq);
	}
}