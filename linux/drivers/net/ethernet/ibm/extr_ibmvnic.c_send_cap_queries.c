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
struct TYPE_2__ {void* capability; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ query_capability; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  running_cap_crqs; } ;
typedef  int /*<<< orphan*/  crq ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int /*<<< orphan*/  MAX_MTU ; 
 int /*<<< orphan*/  MAX_MULTICAST_FILTERS ; 
 int /*<<< orphan*/  MAX_RX_ADD_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  MAX_RX_ADD_QUEUES ; 
 int /*<<< orphan*/  MAX_RX_QUEUES ; 
 int /*<<< orphan*/  MAX_TX_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  MAX_TX_QUEUES ; 
 int /*<<< orphan*/  MAX_TX_SG_ENTRIES ; 
 int /*<<< orphan*/  MIN_MTU ; 
 int /*<<< orphan*/  MIN_RX_ADD_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  MIN_RX_ADD_QUEUES ; 
 int /*<<< orphan*/  MIN_RX_QUEUES ; 
 int /*<<< orphan*/  MIN_TX_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  MIN_TX_QUEUES ; 
 int /*<<< orphan*/  OPT_RXBA_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  OPT_RX_BUFADD_Q_PER_RX_COMP_Q ; 
 int /*<<< orphan*/  OPT_RX_COMP_QUEUES ; 
 int /*<<< orphan*/  OPT_TX_COMP_SUB_QUEUES ; 
 int /*<<< orphan*/  OPT_TX_ENTRIES_PER_SUBCRQ ; 
 int /*<<< orphan*/  PROMISC_SUPPORTED ; 
 int /*<<< orphan*/  QUERY_CAPABILITY ; 
 int /*<<< orphan*/  RX_SG_SUPPORTED ; 
 int /*<<< orphan*/  RX_VLAN_HEADER_INSERTION ; 
 int /*<<< orphan*/  TCP_IP_OFFLOAD ; 
 int /*<<< orphan*/  TX_RX_DESC_REQ ; 
 int /*<<< orphan*/  VLAN_HEADER_INSERTION ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void send_cap_queries(struct ibmvnic_adapter *adapter)
{
	union ibmvnic_crq crq;

	atomic_set(&adapter->running_cap_crqs, 0);
	memset(&crq, 0, sizeof(crq));
	crq.query_capability.first = IBMVNIC_CRQ_CMD;
	crq.query_capability.cmd = QUERY_CAPABILITY;

	crq.query_capability.capability = cpu_to_be16(MIN_TX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_RX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_RX_ADD_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_TX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_RX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_RX_ADD_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MIN_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MIN_RX_ADD_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MAX_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MAX_RX_ADD_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(TCP_IP_OFFLOAD);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(PROMISC_SUPPORTED);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_MTU);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_MTU);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_MULTICAST_FILTERS);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(VLAN_HEADER_INSERTION);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(RX_VLAN_HEADER_INSERTION);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_TX_SG_ENTRIES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(RX_SG_SUPPORTED);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(OPT_TX_COMP_SUB_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(OPT_RX_COMP_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_RX_BUFADD_Q_PER_RX_COMP_Q);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_RXBA_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(TX_RX_DESC_REQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);
}