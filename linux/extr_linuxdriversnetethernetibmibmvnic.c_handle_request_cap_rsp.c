#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* ioba; void* len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
struct TYPE_10__ {int code; } ;
struct TYPE_11__ {TYPE_4__ rc; int /*<<< orphan*/  number; int /*<<< orphan*/  capability; } ;
struct TYPE_8__ {int /*<<< orphan*/  capability; } ;
union ibmvnic_crq {TYPE_6__ query_ip_offload; TYPE_5__ request_capability_rsp; TYPE_2__ request_capability; } ;
typedef  scalar_t__ u64 ;
struct ibmvnic_query_ip_offload_buffer {int dummy; } ;
struct TYPE_9__ {scalar_t__ mtu; } ;
struct ibmvnic_adapter {int wait_capability; int ip_offload_tok; struct ibmvnic_query_ip_offload_buffer ip_offload_buf; int /*<<< orphan*/  running_cap_crqs; TYPE_3__ fallback; scalar_t__ promisc; scalar_t__ req_mtu; scalar_t__ req_rx_add_entries_per_subcrq; scalar_t__ req_tx_entries_per_subcrq; scalar_t__ req_rx_add_queues; scalar_t__ req_rx_queues; scalar_t__ req_tx_queues; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  newcrq ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
#define  PARTIALSUCCESS 136 
#define  PROMISC_REQUESTED 135 
 int /*<<< orphan*/  QUERY_IP_OFFLOAD ; 
#define  REQ_MTU 134 
#define  REQ_RX_ADD_ENTRIES_PER_SUBCRQ 133 
#define  REQ_RX_ADD_QUEUES 132 
#define  REQ_RX_QUEUES 131 
#define  REQ_TX_ENTRIES_PER_SUBCRQ 130 
#define  REQ_TX_QUEUES 129 
#define  SUCCESS 128 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int const be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__,long,char*) ; 
 int dma_map_single (struct device*,struct ibmvnic_query_ip_offload_buffer*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  ibmvnic_send_req_caps (struct ibmvnic_adapter*,int) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static void handle_request_cap_rsp(union ibmvnic_crq *crq,
				   struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;
	u64 *req_value;
	char *name;

	atomic_dec(&adapter->running_cap_crqs);
	switch (be16_to_cpu(crq->request_capability_rsp.capability)) {
	case REQ_TX_QUEUES:
		req_value = &adapter->req_tx_queues;
		name = "tx";
		break;
	case REQ_RX_QUEUES:
		req_value = &adapter->req_rx_queues;
		name = "rx";
		break;
	case REQ_RX_ADD_QUEUES:
		req_value = &adapter->req_rx_add_queues;
		name = "rx_add";
		break;
	case REQ_TX_ENTRIES_PER_SUBCRQ:
		req_value = &adapter->req_tx_entries_per_subcrq;
		name = "tx_entries_per_subcrq";
		break;
	case REQ_RX_ADD_ENTRIES_PER_SUBCRQ:
		req_value = &adapter->req_rx_add_entries_per_subcrq;
		name = "rx_add_entries_per_subcrq";
		break;
	case REQ_MTU:
		req_value = &adapter->req_mtu;
		name = "mtu";
		break;
	case PROMISC_REQUESTED:
		req_value = &adapter->promisc;
		name = "promisc";
		break;
	default:
		dev_err(dev, "Got invalid cap request rsp %d\n",
			crq->request_capability.capability);
		return;
	}

	switch (crq->request_capability_rsp.rc.code) {
	case SUCCESS:
		break;
	case PARTIALSUCCESS:
		dev_info(dev, "req=%lld, rsp=%ld in %s queue, retrying.\n",
			 *req_value,
			 (long int)be64_to_cpu(crq->request_capability_rsp.
					       number), name);

		if (be16_to_cpu(crq->request_capability_rsp.capability) ==
		    REQ_MTU) {
			pr_err("mtu of %llu is not supported. Reverting.\n",
			       *req_value);
			*req_value = adapter->fallback.mtu;
		} else {
			*req_value =
				be64_to_cpu(crq->request_capability_rsp.number);
		}

		ibmvnic_send_req_caps(adapter, 1);
		return;
	default:
		dev_err(dev, "Error %d in request cap rsp\n",
			crq->request_capability_rsp.rc.code);
		return;
	}

	/* Done receiving requested capabilities, query IP offload support */
	if (atomic_read(&adapter->running_cap_crqs) == 0) {
		union ibmvnic_crq newcrq;
		int buf_sz = sizeof(struct ibmvnic_query_ip_offload_buffer);
		struct ibmvnic_query_ip_offload_buffer *ip_offload_buf =
		    &adapter->ip_offload_buf;

		adapter->wait_capability = false;
		adapter->ip_offload_tok = dma_map_single(dev, ip_offload_buf,
							 buf_sz,
							 DMA_FROM_DEVICE);

		if (dma_mapping_error(dev, adapter->ip_offload_tok)) {
			if (!firmware_has_feature(FW_FEATURE_CMO))
				dev_err(dev, "Couldn't map offload buffer\n");
			return;
		}

		memset(&newcrq, 0, sizeof(newcrq));
		newcrq.query_ip_offload.first = IBMVNIC_CRQ_CMD;
		newcrq.query_ip_offload.cmd = QUERY_IP_OFFLOAD;
		newcrq.query_ip_offload.len = cpu_to_be32(buf_sz);
		newcrq.query_ip_offload.ioba =
		    cpu_to_be32(adapter->ip_offload_tok);

		ibmvnic_send_crq(adapter, &newcrq);
	}
}