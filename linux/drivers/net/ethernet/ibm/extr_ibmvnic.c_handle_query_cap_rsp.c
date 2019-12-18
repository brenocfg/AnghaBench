#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long code; } ;
struct TYPE_6__ {scalar_t__ number; int /*<<< orphan*/  capability; TYPE_2__ rc; } ;
union ibmvnic_crq {TYPE_3__ query_capability; } ;
struct net_device {int /*<<< orphan*/  features; void* max_mtu; void* min_mtu; } ;
struct ibmvnic_adapter {scalar_t__ min_tx_queues; scalar_t__ min_rx_queues; scalar_t__ min_rx_add_queues; scalar_t__ max_tx_queues; scalar_t__ max_rx_queues; scalar_t__ max_rx_add_queues; scalar_t__ min_tx_entries_per_subcrq; scalar_t__ min_rx_add_entries_per_subcrq; scalar_t__ max_tx_entries_per_subcrq; scalar_t__ max_rx_add_entries_per_subcrq; scalar_t__ tcp_ip_offload; scalar_t__ promisc_supported; void* min_mtu; void* max_mtu; scalar_t__ max_multicast_filters; scalar_t__ vlan_header_insertion; scalar_t__ rx_vlan_header_insertion; scalar_t__ max_tx_sg_entries; scalar_t__ rx_sg_supported; scalar_t__ opt_tx_comp_sub_queues; scalar_t__ opt_rx_comp_queues; scalar_t__ opt_rx_bufadd_q_per_rx_comp_q; scalar_t__ opt_tx_entries_per_subcrq; scalar_t__ opt_rxba_entries_per_subcrq; scalar_t__ tx_rx_desc_req; int wait_capability; int /*<<< orphan*/  running_cap_crqs; TYPE_1__* vdev; struct net_device* netdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 void* ETH_HLEN ; 
#define  MAX_MTU 152 
#define  MAX_MULTICAST_FILTERS 151 
#define  MAX_RX_ADD_ENTRIES_PER_SUBCRQ 150 
#define  MAX_RX_ADD_QUEUES 149 
#define  MAX_RX_QUEUES 148 
#define  MAX_TX_ENTRIES_PER_SUBCRQ 147 
#define  MAX_TX_QUEUES 146 
#define  MAX_TX_SG_ENTRIES 145 
#define  MIN_MTU 144 
#define  MIN_RX_ADD_ENTRIES_PER_SUBCRQ 143 
#define  MIN_RX_ADD_QUEUES 142 
#define  MIN_RX_QUEUES 141 
#define  MIN_TX_ENTRIES_PER_SUBCRQ 140 
#define  MIN_TX_QUEUES 139 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_STAG_TX ; 
#define  OPT_RXBA_ENTRIES_PER_SUBCRQ 138 
#define  OPT_RX_BUFADD_Q_PER_RX_COMP_Q 137 
#define  OPT_RX_COMP_QUEUES 136 
#define  OPT_TX_COMP_SUB_QUEUES 135 
#define  OPT_TX_ENTRIES_PER_SUBCRQ 134 
#define  PROMISC_SUPPORTED 133 
#define  RX_SG_SUPPORTED 132 
#define  RX_VLAN_HEADER_INSERTION 131 
#define  TCP_IP_OFFLOAD 130 
#define  TX_RX_DESC_REQ 129 
#define  VLAN_HEADER_INSERTION 128 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 int /*<<< orphan*/  ibmvnic_send_req_caps (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_query_cap_rsp(union ibmvnic_crq *crq,
				 struct ibmvnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct device *dev = &adapter->vdev->dev;
	long rc;

	atomic_dec(&adapter->running_cap_crqs);
	netdev_dbg(netdev, "Outstanding queries: %d\n",
		   atomic_read(&adapter->running_cap_crqs));
	rc = crq->query_capability.rc.code;
	if (rc) {
		dev_err(dev, "Error %ld in QUERY_CAP_RSP\n", rc);
		goto out;
	}

	switch (be16_to_cpu(crq->query_capability.capability)) {
	case MIN_TX_QUEUES:
		adapter->min_tx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_tx_queues = %lld\n",
			   adapter->min_tx_queues);
		break;
	case MIN_RX_QUEUES:
		adapter->min_rx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_queues = %lld\n",
			   adapter->min_rx_queues);
		break;
	case MIN_RX_ADD_QUEUES:
		adapter->min_rx_add_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_add_queues = %lld\n",
			   adapter->min_rx_add_queues);
		break;
	case MAX_TX_QUEUES:
		adapter->max_tx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_queues = %lld\n",
			   adapter->max_tx_queues);
		break;
	case MAX_RX_QUEUES:
		adapter->max_rx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_queues = %lld\n",
			   adapter->max_rx_queues);
		break;
	case MAX_RX_ADD_QUEUES:
		adapter->max_rx_add_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_add_queues = %lld\n",
			   adapter->max_rx_add_queues);
		break;
	case MIN_TX_ENTRIES_PER_SUBCRQ:
		adapter->min_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_tx_entries_per_subcrq = %lld\n",
			   adapter->min_tx_entries_per_subcrq);
		break;
	case MIN_RX_ADD_ENTRIES_PER_SUBCRQ:
		adapter->min_rx_add_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_add_entrs_per_subcrq = %lld\n",
			   adapter->min_rx_add_entries_per_subcrq);
		break;
	case MAX_TX_ENTRIES_PER_SUBCRQ:
		adapter->max_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_entries_per_subcrq = %lld\n",
			   adapter->max_tx_entries_per_subcrq);
		break;
	case MAX_RX_ADD_ENTRIES_PER_SUBCRQ:
		adapter->max_rx_add_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_add_entrs_per_subcrq = %lld\n",
			   adapter->max_rx_add_entries_per_subcrq);
		break;
	case TCP_IP_OFFLOAD:
		adapter->tcp_ip_offload =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "tcp_ip_offload = %lld\n",
			   adapter->tcp_ip_offload);
		break;
	case PROMISC_SUPPORTED:
		adapter->promisc_supported =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "promisc_supported = %lld\n",
			   adapter->promisc_supported);
		break;
	case MIN_MTU:
		adapter->min_mtu = be64_to_cpu(crq->query_capability.number);
		netdev->min_mtu = adapter->min_mtu - ETH_HLEN;
		netdev_dbg(netdev, "min_mtu = %lld\n", adapter->min_mtu);
		break;
	case MAX_MTU:
		adapter->max_mtu = be64_to_cpu(crq->query_capability.number);
		netdev->max_mtu = adapter->max_mtu - ETH_HLEN;
		netdev_dbg(netdev, "max_mtu = %lld\n", adapter->max_mtu);
		break;
	case MAX_MULTICAST_FILTERS:
		adapter->max_multicast_filters =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_multicast_filters = %lld\n",
			   adapter->max_multicast_filters);
		break;
	case VLAN_HEADER_INSERTION:
		adapter->vlan_header_insertion =
		    be64_to_cpu(crq->query_capability.number);
		if (adapter->vlan_header_insertion)
			netdev->features |= NETIF_F_HW_VLAN_STAG_TX;
		netdev_dbg(netdev, "vlan_header_insertion = %lld\n",
			   adapter->vlan_header_insertion);
		break;
	case RX_VLAN_HEADER_INSERTION:
		adapter->rx_vlan_header_insertion =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "rx_vlan_header_insertion = %lld\n",
			   adapter->rx_vlan_header_insertion);
		break;
	case MAX_TX_SG_ENTRIES:
		adapter->max_tx_sg_entries =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_sg_entries = %lld\n",
			   adapter->max_tx_sg_entries);
		break;
	case RX_SG_SUPPORTED:
		adapter->rx_sg_supported =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "rx_sg_supported = %lld\n",
			   adapter->rx_sg_supported);
		break;
	case OPT_TX_COMP_SUB_QUEUES:
		adapter->opt_tx_comp_sub_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_tx_comp_sub_queues = %lld\n",
			   adapter->opt_tx_comp_sub_queues);
		break;
	case OPT_RX_COMP_QUEUES:
		adapter->opt_rx_comp_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rx_comp_queues = %lld\n",
			   adapter->opt_rx_comp_queues);
		break;
	case OPT_RX_BUFADD_Q_PER_RX_COMP_Q:
		adapter->opt_rx_bufadd_q_per_rx_comp_q =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rx_bufadd_q_per_rx_comp_q = %lld\n",
			   adapter->opt_rx_bufadd_q_per_rx_comp_q);
		break;
	case OPT_TX_ENTRIES_PER_SUBCRQ:
		adapter->opt_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_tx_entries_per_subcrq = %lld\n",
			   adapter->opt_tx_entries_per_subcrq);
		break;
	case OPT_RXBA_ENTRIES_PER_SUBCRQ:
		adapter->opt_rxba_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rxba_entries_per_subcrq = %lld\n",
			   adapter->opt_rxba_entries_per_subcrq);
		break;
	case TX_RX_DESC_REQ:
		adapter->tx_rx_desc_req = crq->query_capability.number;
		netdev_dbg(netdev, "tx_rx_desc_req = %llx\n",
			   adapter->tx_rx_desc_req);
		break;

	default:
		netdev_err(netdev, "Got invalid cap rsp %d\n",
			   crq->query_capability.capability);
	}

out:
	if (atomic_read(&adapter->running_cap_crqs) == 0) {
		adapter->wait_capability = false;
		ibmvnic_send_req_caps(adapter, 0);
	}
}