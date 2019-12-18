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
struct TYPE_5__ {void* ioba; void* len; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_1__ control_ip_offload; } ;
struct ibmvnic_query_ip_offload_buffer {unsigned long ipv4_chksum; unsigned long ipv6_chksum; unsigned long tcp_ipv4_chksum; unsigned long tcp_ipv6_chksum; unsigned long udp_ipv4_chksum; unsigned long udp_ipv6_chksum; unsigned long large_tx_ipv4; unsigned long large_tx_ipv6; unsigned long large_rx_ipv4; unsigned long large_rx_ipv6; unsigned long max_ipv4_header_size; unsigned long max_ipv6_header_size; unsigned long max_tcp_header_size; unsigned long max_udp_header_size; unsigned long max_large_tx_size; unsigned long max_large_rx_size; unsigned long ipv6_extension_header; unsigned long tcp_pseudosum_req; unsigned long num_ipv6_ext_headers; unsigned long off_ipv6_ext_headers; } ;
struct TYPE_8__ {unsigned long ipv4_chksum; unsigned long ipv6_chksum; unsigned long tcp_ipv4_chksum; unsigned long udp_ipv4_chksum; unsigned long tcp_ipv6_chksum; unsigned long udp_ipv6_chksum; unsigned long large_tx_ipv4; unsigned long large_tx_ipv6; scalar_t__ large_rx_ipv6; scalar_t__ large_rx_ipv4; void* version; void* len; } ;
struct ibmvnic_adapter {int ip_offload_ctrl_tok; scalar_t__ state; TYPE_3__* netdev; TYPE_4__ ip_offload_ctrl; int /*<<< orphan*/  ip_offload_tok; struct ibmvnic_query_ip_offload_buffer ip_offload_buf; TYPE_2__* vdev; } ;
struct device {int dummy; } ;
typedef  int netdev_features_t ;
typedef  int /*<<< orphan*/  crq ;
struct TYPE_7__ {int hw_features; int features; int wanted_features; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_IP_OFFLOAD ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int INITIAL_VERSION_IOB ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GSO ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 scalar_t__ VNIC_PROBING ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_map_single (struct device*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*,...) ; 

__attribute__((used)) static void handle_query_ip_offload_rsp(struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;
	struct ibmvnic_query_ip_offload_buffer *buf = &adapter->ip_offload_buf;
	netdev_features_t old_hw_features = 0;
	union ibmvnic_crq crq;
	int i;

	dma_unmap_single(dev, adapter->ip_offload_tok,
			 sizeof(adapter->ip_offload_buf), DMA_FROM_DEVICE);

	netdev_dbg(adapter->netdev, "Query IP Offload Buffer:\n");
	for (i = 0; i < (sizeof(adapter->ip_offload_buf) - 1) / 8 + 1; i++)
		netdev_dbg(adapter->netdev, "%016lx\n",
			   ((unsigned long int *)(buf))[i]);

	netdev_dbg(adapter->netdev, "ipv4_chksum = %d\n", buf->ipv4_chksum);
	netdev_dbg(adapter->netdev, "ipv6_chksum = %d\n", buf->ipv6_chksum);
	netdev_dbg(adapter->netdev, "tcp_ipv4_chksum = %d\n",
		   buf->tcp_ipv4_chksum);
	netdev_dbg(adapter->netdev, "tcp_ipv6_chksum = %d\n",
		   buf->tcp_ipv6_chksum);
	netdev_dbg(adapter->netdev, "udp_ipv4_chksum = %d\n",
		   buf->udp_ipv4_chksum);
	netdev_dbg(adapter->netdev, "udp_ipv6_chksum = %d\n",
		   buf->udp_ipv6_chksum);
	netdev_dbg(adapter->netdev, "large_tx_ipv4 = %d\n",
		   buf->large_tx_ipv4);
	netdev_dbg(adapter->netdev, "large_tx_ipv6 = %d\n",
		   buf->large_tx_ipv6);
	netdev_dbg(adapter->netdev, "large_rx_ipv4 = %d\n",
		   buf->large_rx_ipv4);
	netdev_dbg(adapter->netdev, "large_rx_ipv6 = %d\n",
		   buf->large_rx_ipv6);
	netdev_dbg(adapter->netdev, "max_ipv4_hdr_sz = %d\n",
		   buf->max_ipv4_header_size);
	netdev_dbg(adapter->netdev, "max_ipv6_hdr_sz = %d\n",
		   buf->max_ipv6_header_size);
	netdev_dbg(adapter->netdev, "max_tcp_hdr_size = %d\n",
		   buf->max_tcp_header_size);
	netdev_dbg(adapter->netdev, "max_udp_hdr_size = %d\n",
		   buf->max_udp_header_size);
	netdev_dbg(adapter->netdev, "max_large_tx_size = %d\n",
		   buf->max_large_tx_size);
	netdev_dbg(adapter->netdev, "max_large_rx_size = %d\n",
		   buf->max_large_rx_size);
	netdev_dbg(adapter->netdev, "ipv6_ext_hdr = %d\n",
		   buf->ipv6_extension_header);
	netdev_dbg(adapter->netdev, "tcp_pseudosum_req = %d\n",
		   buf->tcp_pseudosum_req);
	netdev_dbg(adapter->netdev, "num_ipv6_ext_hd = %d\n",
		   buf->num_ipv6_ext_headers);
	netdev_dbg(adapter->netdev, "off_ipv6_ext_hd = %d\n",
		   buf->off_ipv6_ext_headers);

	adapter->ip_offload_ctrl_tok =
	    dma_map_single(dev, &adapter->ip_offload_ctrl,
			   sizeof(adapter->ip_offload_ctrl), DMA_TO_DEVICE);

	if (dma_mapping_error(dev, adapter->ip_offload_ctrl_tok)) {
		dev_err(dev, "Couldn't map ip offload control buffer\n");
		return;
	}

	adapter->ip_offload_ctrl.len =
	    cpu_to_be32(sizeof(adapter->ip_offload_ctrl));
	adapter->ip_offload_ctrl.version = cpu_to_be32(INITIAL_VERSION_IOB);
	adapter->ip_offload_ctrl.ipv4_chksum = buf->ipv4_chksum;
	adapter->ip_offload_ctrl.ipv6_chksum = buf->ipv6_chksum;
	adapter->ip_offload_ctrl.tcp_ipv4_chksum = buf->tcp_ipv4_chksum;
	adapter->ip_offload_ctrl.udp_ipv4_chksum = buf->udp_ipv4_chksum;
	adapter->ip_offload_ctrl.tcp_ipv6_chksum = buf->tcp_ipv6_chksum;
	adapter->ip_offload_ctrl.udp_ipv6_chksum = buf->udp_ipv6_chksum;
	adapter->ip_offload_ctrl.large_tx_ipv4 = buf->large_tx_ipv4;
	adapter->ip_offload_ctrl.large_tx_ipv6 = buf->large_tx_ipv6;

	/* large_rx disabled for now, additional features needed */
	adapter->ip_offload_ctrl.large_rx_ipv4 = 0;
	adapter->ip_offload_ctrl.large_rx_ipv6 = 0;

	if (adapter->state != VNIC_PROBING) {
		old_hw_features = adapter->netdev->hw_features;
		adapter->netdev->hw_features = 0;
	}

	adapter->netdev->hw_features = NETIF_F_SG | NETIF_F_GSO | NETIF_F_GRO;

	if (buf->tcp_ipv4_chksum || buf->udp_ipv4_chksum)
		adapter->netdev->hw_features |= NETIF_F_IP_CSUM;

	if (buf->tcp_ipv6_chksum || buf->udp_ipv6_chksum)
		adapter->netdev->hw_features |= NETIF_F_IPV6_CSUM;

	if ((adapter->netdev->features &
	    (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)))
		adapter->netdev->hw_features |= NETIF_F_RXCSUM;

	if (buf->large_tx_ipv4)
		adapter->netdev->hw_features |= NETIF_F_TSO;
	if (buf->large_tx_ipv6)
		adapter->netdev->hw_features |= NETIF_F_TSO6;

	if (adapter->state == VNIC_PROBING) {
		adapter->netdev->features |= adapter->netdev->hw_features;
	} else if (old_hw_features != adapter->netdev->hw_features) {
		netdev_features_t tmp = 0;

		/* disable features no longer supported */
		adapter->netdev->features &= adapter->netdev->hw_features;
		/* turn on features now supported if previously enabled */
		tmp = (old_hw_features ^ adapter->netdev->hw_features) &
			adapter->netdev->hw_features;
		adapter->netdev->features |=
				tmp & adapter->netdev->wanted_features;
	}

	memset(&crq, 0, sizeof(crq));
	crq.control_ip_offload.first = IBMVNIC_CRQ_CMD;
	crq.control_ip_offload.cmd = CONTROL_IP_OFFLOAD;
	crq.control_ip_offload.len =
	    cpu_to_be32(sizeof(adapter->ip_offload_ctrl));
	crq.control_ip_offload.ioba = cpu_to_be32(adapter->ip_offload_ctrl_tok);
	ibmvnic_send_crq(adapter, &crq);
}