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
struct TYPE_8__ {void* len; void* ioba; int /*<<< orphan*/  cmd; int /*<<< orphan*/  first; } ;
union ibmvnic_crq {TYPE_4__ login; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct vnic_login_client_data {int dummy; } ;
struct ibmvnic_login_rsp_buffer {void* client_data_len; void* client_data_offset; void* login_rsp_len; void* login_rsp_ioba; void* off_rxcomp_subcrqs; void* num_rxcomp_subcrqs; void* off_txcomp_subcrqs; void* num_txcomp_subcrqs; void* version; void* len; } ;
struct ibmvnic_login_buffer {void* client_data_len; void* client_data_offset; void* login_rsp_len; void* login_rsp_ioba; void* off_rxcomp_subcrqs; void* num_rxcomp_subcrqs; void* off_txcomp_subcrqs; void* num_txcomp_subcrqs; void* version; void* len; } ;
struct ibmvnic_adapter {int req_tx_queues; int req_rx_queues; size_t login_buf_token; size_t login_buf_sz; size_t login_rsp_buf_token; size_t login_rsp_buf_sz; struct ibmvnic_login_rsp_buffer* login_buf; int /*<<< orphan*/  netdev; TYPE_3__** rx_scrq; TYPE_2__** tx_scrq; struct ibmvnic_login_rsp_buffer* login_rsp_buf; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
typedef  size_t dma_addr_t ;
typedef  int /*<<< orphan*/  crq ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_7__ {int /*<<< orphan*/  crq_num; } ;
struct TYPE_6__ {int /*<<< orphan*/  crq_num; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IBMVNIC_CRQ_CMD ; 
 int IBMVNIC_TX_DESC_VERSIONS ; 
 size_t INITIAL_VERSION_LB ; 
 int /*<<< orphan*/  LOGIN ; 
 void* cpu_to_be32 (size_t) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 size_t dma_map_single (struct device*,struct ibmvnic_login_rsp_buffer*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,size_t) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvnic_send_crq (struct ibmvnic_adapter*,union ibmvnic_crq*) ; 
 int /*<<< orphan*/  kfree (struct ibmvnic_login_rsp_buffer*) ; 
 struct ibmvnic_login_rsp_buffer* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct ibmvnic_login_rsp_buffer* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union ibmvnic_crq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_login_rsp_buffer (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  vnic_add_client_data (struct ibmvnic_adapter*,struct vnic_login_client_data*) ; 
 int vnic_client_data_len (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int send_login(struct ibmvnic_adapter *adapter)
{
	struct ibmvnic_login_rsp_buffer *login_rsp_buffer;
	struct ibmvnic_login_buffer *login_buffer;
	struct device *dev = &adapter->vdev->dev;
	dma_addr_t rsp_buffer_token;
	dma_addr_t buffer_token;
	size_t rsp_buffer_size;
	union ibmvnic_crq crq;
	size_t buffer_size;
	__be64 *tx_list_p;
	__be64 *rx_list_p;
	int client_data_len;
	struct vnic_login_client_data *vlcd;
	int i;

	if (!adapter->tx_scrq || !adapter->rx_scrq) {
		netdev_err(adapter->netdev,
			   "RX or TX queues are not allocated, device login failed\n");
		return -1;
	}

	release_login_rsp_buffer(adapter);
	client_data_len = vnic_client_data_len(adapter);

	buffer_size =
	    sizeof(struct ibmvnic_login_buffer) +
	    sizeof(u64) * (adapter->req_tx_queues + adapter->req_rx_queues) +
	    client_data_len;

	login_buffer = kzalloc(buffer_size, GFP_ATOMIC);
	if (!login_buffer)
		goto buf_alloc_failed;

	buffer_token = dma_map_single(dev, login_buffer, buffer_size,
				      DMA_TO_DEVICE);
	if (dma_mapping_error(dev, buffer_token)) {
		dev_err(dev, "Couldn't map login buffer\n");
		goto buf_map_failed;
	}

	rsp_buffer_size = sizeof(struct ibmvnic_login_rsp_buffer) +
			  sizeof(u64) * adapter->req_tx_queues +
			  sizeof(u64) * adapter->req_rx_queues +
			  sizeof(u64) * adapter->req_rx_queues +
			  sizeof(u8) * IBMVNIC_TX_DESC_VERSIONS;

	login_rsp_buffer = kmalloc(rsp_buffer_size, GFP_ATOMIC);
	if (!login_rsp_buffer)
		goto buf_rsp_alloc_failed;

	rsp_buffer_token = dma_map_single(dev, login_rsp_buffer,
					  rsp_buffer_size, DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, rsp_buffer_token)) {
		dev_err(dev, "Couldn't map login rsp buffer\n");
		goto buf_rsp_map_failed;
	}

	adapter->login_buf = login_buffer;
	adapter->login_buf_token = buffer_token;
	adapter->login_buf_sz = buffer_size;
	adapter->login_rsp_buf = login_rsp_buffer;
	adapter->login_rsp_buf_token = rsp_buffer_token;
	adapter->login_rsp_buf_sz = rsp_buffer_size;

	login_buffer->len = cpu_to_be32(buffer_size);
	login_buffer->version = cpu_to_be32(INITIAL_VERSION_LB);
	login_buffer->num_txcomp_subcrqs = cpu_to_be32(adapter->req_tx_queues);
	login_buffer->off_txcomp_subcrqs =
	    cpu_to_be32(sizeof(struct ibmvnic_login_buffer));
	login_buffer->num_rxcomp_subcrqs = cpu_to_be32(adapter->req_rx_queues);
	login_buffer->off_rxcomp_subcrqs =
	    cpu_to_be32(sizeof(struct ibmvnic_login_buffer) +
			sizeof(u64) * adapter->req_tx_queues);
	login_buffer->login_rsp_ioba = cpu_to_be32(rsp_buffer_token);
	login_buffer->login_rsp_len = cpu_to_be32(rsp_buffer_size);

	tx_list_p = (__be64 *)((char *)login_buffer +
				      sizeof(struct ibmvnic_login_buffer));
	rx_list_p = (__be64 *)((char *)login_buffer +
				      sizeof(struct ibmvnic_login_buffer) +
				      sizeof(u64) * adapter->req_tx_queues);

	for (i = 0; i < adapter->req_tx_queues; i++) {
		if (adapter->tx_scrq[i]) {
			tx_list_p[i] = cpu_to_be64(adapter->tx_scrq[i]->
						   crq_num);
		}
	}

	for (i = 0; i < adapter->req_rx_queues; i++) {
		if (adapter->rx_scrq[i]) {
			rx_list_p[i] = cpu_to_be64(adapter->rx_scrq[i]->
						   crq_num);
		}
	}

	/* Insert vNIC login client data */
	vlcd = (struct vnic_login_client_data *)
		((char *)rx_list_p + (sizeof(u64) * adapter->req_rx_queues));
	login_buffer->client_data_offset =
			cpu_to_be32((char *)vlcd - (char *)login_buffer);
	login_buffer->client_data_len = cpu_to_be32(client_data_len);

	vnic_add_client_data(adapter, vlcd);

	netdev_dbg(adapter->netdev, "Login Buffer:\n");
	for (i = 0; i < (adapter->login_buf_sz - 1) / 8 + 1; i++) {
		netdev_dbg(adapter->netdev, "%016lx\n",
			   ((unsigned long int *)(adapter->login_buf))[i]);
	}

	memset(&crq, 0, sizeof(crq));
	crq.login.first = IBMVNIC_CRQ_CMD;
	crq.login.cmd = LOGIN;
	crq.login.ioba = cpu_to_be32(buffer_token);
	crq.login.len = cpu_to_be32(buffer_size);
	ibmvnic_send_crq(adapter, &crq);

	return 0;

buf_rsp_map_failed:
	kfree(login_rsp_buffer);
buf_rsp_alloc_failed:
	dma_unmap_single(dev, buffer_token, buffer_size, DMA_TO_DEVICE);
buf_map_failed:
	kfree(login_buffer);
buf_alloc_failed:
	return -1;
}