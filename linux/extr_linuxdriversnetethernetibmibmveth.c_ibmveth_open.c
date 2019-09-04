#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags_len; int /*<<< orphan*/  address; } ;
union ibmveth_buf_desc {int /*<<< orphan*/  desc; TYPE_1__ fields; } ;
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int mtu; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct ibmveth_rx_q_entry {int dummy; } ;
struct TYPE_7__ {int queue_len; int num_slots; int toggle; int /*<<< orphan*/  queue_dma; int /*<<< orphan*/  queue_addr; scalar_t__ index; } ;
struct ibmveth_adapter {int /*<<< orphan*/  napi; void* buffer_list_addr; void* filter_list_addr; TYPE_2__ rx_queue; void* buffer_list_dma; void* filter_list_dma; TYPE_4__* rx_buff_pool; void* bounce_buffer; void* bounce_buffer_dma; TYPE_3__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_9__ {scalar_t__ active; scalar_t__ size; } ;
struct TYPE_8__ {struct device dev; int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int ENONET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long H_BUSY ; 
 scalar_t__ H_IS_LONG_BUSY (unsigned long) ; 
 unsigned long H_SUCCESS ; 
 int IBMVETH_BUFF_OH ; 
 int IBMVETH_BUF_VALID ; 
 int IBMVETH_NUM_BUFF_POOLS ; 
 int /*<<< orphan*/  VIO_IRQ_DISABLE ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 unsigned long h_free_logical_lan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_vio_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ibmveth_alloc_buffer_pool (TYPE_4__*) ; 
 int /*<<< orphan*/  ibmveth_encode_mac_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmveth_free_buffer_pool (struct ibmveth_adapter*,TYPE_4__*) ; 
 int /*<<< orphan*/  ibmveth_interrupt (int /*<<< orphan*/ ,struct net_device*) ; 
 unsigned long ibmveth_register_logical_lan (struct ibmveth_adapter*,union ibmveth_buf_desc,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct net_device*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ibmveth_open(struct net_device *netdev)
{
	struct ibmveth_adapter *adapter = netdev_priv(netdev);
	u64 mac_address;
	int rxq_entries = 1;
	unsigned long lpar_rc;
	int rc;
	union ibmveth_buf_desc rxq_desc;
	int i;
	struct device *dev;

	netdev_dbg(netdev, "open starting\n");

	napi_enable(&adapter->napi);

	for(i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++)
		rxq_entries += adapter->rx_buff_pool[i].size;

	rc = -ENOMEM;
	adapter->buffer_list_addr = (void*) get_zeroed_page(GFP_KERNEL);
	if (!adapter->buffer_list_addr) {
		netdev_err(netdev, "unable to allocate list pages\n");
		goto out;
	}

	adapter->filter_list_addr = (void*) get_zeroed_page(GFP_KERNEL);
	if (!adapter->filter_list_addr) {
		netdev_err(netdev, "unable to allocate filter pages\n");
		goto out_free_buffer_list;
	}

	dev = &adapter->vdev->dev;

	adapter->rx_queue.queue_len = sizeof(struct ibmveth_rx_q_entry) *
						rxq_entries;
	adapter->rx_queue.queue_addr =
		dma_alloc_coherent(dev, adapter->rx_queue.queue_len,
				   &adapter->rx_queue.queue_dma, GFP_KERNEL);
	if (!adapter->rx_queue.queue_addr)
		goto out_free_filter_list;

	adapter->buffer_list_dma = dma_map_single(dev,
			adapter->buffer_list_addr, 4096, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, adapter->buffer_list_dma)) {
		netdev_err(netdev, "unable to map buffer list pages\n");
		goto out_free_queue_mem;
	}

	adapter->filter_list_dma = dma_map_single(dev,
			adapter->filter_list_addr, 4096, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, adapter->filter_list_dma)) {
		netdev_err(netdev, "unable to map filter list pages\n");
		goto out_unmap_buffer_list;
	}

	adapter->rx_queue.index = 0;
	adapter->rx_queue.num_slots = rxq_entries;
	adapter->rx_queue.toggle = 1;

	mac_address = ibmveth_encode_mac_addr(netdev->dev_addr);

	rxq_desc.fields.flags_len = IBMVETH_BUF_VALID |
					adapter->rx_queue.queue_len;
	rxq_desc.fields.address = adapter->rx_queue.queue_dma;

	netdev_dbg(netdev, "buffer list @ 0x%p\n", adapter->buffer_list_addr);
	netdev_dbg(netdev, "filter list @ 0x%p\n", adapter->filter_list_addr);
	netdev_dbg(netdev, "receive q   @ 0x%p\n", adapter->rx_queue.queue_addr);

	h_vio_signal(adapter->vdev->unit_address, VIO_IRQ_DISABLE);

	lpar_rc = ibmveth_register_logical_lan(adapter, rxq_desc, mac_address);

	if (lpar_rc != H_SUCCESS) {
		netdev_err(netdev, "h_register_logical_lan failed with %ld\n",
			   lpar_rc);
		netdev_err(netdev, "buffer TCE:0x%llx filter TCE:0x%llx rxq "
			   "desc:0x%llx MAC:0x%llx\n",
				     adapter->buffer_list_dma,
				     adapter->filter_list_dma,
				     rxq_desc.desc,
				     mac_address);
		rc = -ENONET;
		goto out_unmap_filter_list;
	}

	for (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) {
		if (!adapter->rx_buff_pool[i].active)
			continue;
		if (ibmveth_alloc_buffer_pool(&adapter->rx_buff_pool[i])) {
			netdev_err(netdev, "unable to alloc pool\n");
			adapter->rx_buff_pool[i].active = 0;
			rc = -ENOMEM;
			goto out_free_buffer_pools;
		}
	}

	netdev_dbg(netdev, "registering irq 0x%x\n", netdev->irq);
	rc = request_irq(netdev->irq, ibmveth_interrupt, 0, netdev->name,
			 netdev);
	if (rc != 0) {
		netdev_err(netdev, "unable to request irq 0x%x, rc %d\n",
			   netdev->irq, rc);
		do {
			lpar_rc = h_free_logical_lan(adapter->vdev->unit_address);
		} while (H_IS_LONG_BUSY(lpar_rc) || (lpar_rc == H_BUSY));

		goto out_free_buffer_pools;
	}

	rc = -ENOMEM;
	adapter->bounce_buffer =
	    kmalloc(netdev->mtu + IBMVETH_BUFF_OH, GFP_KERNEL);
	if (!adapter->bounce_buffer)
		goto out_free_irq;

	adapter->bounce_buffer_dma =
	    dma_map_single(&adapter->vdev->dev, adapter->bounce_buffer,
			   netdev->mtu + IBMVETH_BUFF_OH, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, adapter->bounce_buffer_dma)) {
		netdev_err(netdev, "unable to map bounce buffer\n");
		goto out_free_bounce_buffer;
	}

	netdev_dbg(netdev, "initial replenish cycle\n");
	ibmveth_interrupt(netdev->irq, netdev);

	netif_start_queue(netdev);

	netdev_dbg(netdev, "open complete\n");

	return 0;

out_free_bounce_buffer:
	kfree(adapter->bounce_buffer);
out_free_irq:
	free_irq(netdev->irq, netdev);
out_free_buffer_pools:
	while (--i >= 0) {
		if (adapter->rx_buff_pool[i].active)
			ibmveth_free_buffer_pool(adapter,
						 &adapter->rx_buff_pool[i]);
	}
out_unmap_filter_list:
	dma_unmap_single(dev, adapter->filter_list_dma, 4096,
			 DMA_BIDIRECTIONAL);
out_unmap_buffer_list:
	dma_unmap_single(dev, adapter->buffer_list_dma, 4096,
			 DMA_BIDIRECTIONAL);
out_free_queue_mem:
	dma_free_coherent(dev, adapter->rx_queue.queue_len,
			  adapter->rx_queue.queue_addr,
			  adapter->rx_queue.queue_dma);
out_free_filter_list:
	free_page((unsigned long)adapter->filter_list_addr);
out_free_buffer_list:
	free_page((unsigned long)adapter->buffer_list_addr);
out:
	napi_disable(&adapter->napi);
	return rc;
}