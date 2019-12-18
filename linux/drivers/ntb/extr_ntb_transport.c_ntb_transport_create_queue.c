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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ntb_transport_qp {int rx_alloc_entry; int tx_max_entry; TYPE_2__* rx_dma_chan; TYPE_2__* tx_dma_chan; int /*<<< orphan*/  tx_mw_size; scalar_t__ tx_mw_dma_addr; int /*<<< orphan*/  rx_free_q; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  ndev; int /*<<< orphan*/  tx_mw_phys; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  tx_handler; int /*<<< orphan*/  rx_handler; void* cb_data; } ;
struct ntb_transport_ctx {int /*<<< orphan*/  qp_bitmap_free; struct ntb_transport_qp* qp_vec; } ;
struct ntb_queue_handlers {int /*<<< orphan*/  event_handler; int /*<<< orphan*/  tx_handler; int /*<<< orphan*/  rx_handler; } ;
struct ntb_queue_entry {int /*<<< orphan*/  entry; struct ntb_transport_qp* qp; } ;
struct ntb_dev {int /*<<< orphan*/  dev; struct ntb_transport_ctx* ctx; struct pci_dev* pdev; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NTB_QP_DEF_NUM_ENTRIES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct ntb_dev* dev_ntb (int /*<<< orphan*/ ) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_2__*) ; 
 void* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_resource (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ntb_queue_entry*) ; 
 struct ntb_queue_entry* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntb_db_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_db_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_dma_filter_fn ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ use_dma ; 

struct ntb_transport_qp *
ntb_transport_create_queue(void *data, struct device *client_dev,
			   const struct ntb_queue_handlers *handlers)
{
	struct ntb_dev *ndev;
	struct pci_dev *pdev;
	struct ntb_transport_ctx *nt;
	struct ntb_queue_entry *entry;
	struct ntb_transport_qp *qp;
	u64 qp_bit;
	unsigned int free_queue;
	dma_cap_mask_t dma_mask;
	int node;
	int i;

	ndev = dev_ntb(client_dev->parent);
	pdev = ndev->pdev;
	nt = ndev->ctx;

	node = dev_to_node(&ndev->dev);

	free_queue = ffs(nt->qp_bitmap_free);
	if (!free_queue)
		goto err;

	/* decrement free_queue to make it zero based */
	free_queue--;

	qp = &nt->qp_vec[free_queue];
	qp_bit = BIT_ULL(qp->qp_num);

	nt->qp_bitmap_free &= ~qp_bit;

	qp->cb_data = data;
	qp->rx_handler = handlers->rx_handler;
	qp->tx_handler = handlers->tx_handler;
	qp->event_handler = handlers->event_handler;

	dma_cap_zero(dma_mask);
	dma_cap_set(DMA_MEMCPY, dma_mask);

	if (use_dma) {
		qp->tx_dma_chan =
			dma_request_channel(dma_mask, ntb_dma_filter_fn,
					    (void *)(unsigned long)node);
		if (!qp->tx_dma_chan)
			dev_info(&pdev->dev, "Unable to allocate TX DMA channel\n");

		qp->rx_dma_chan =
			dma_request_channel(dma_mask, ntb_dma_filter_fn,
					    (void *)(unsigned long)node);
		if (!qp->rx_dma_chan)
			dev_info(&pdev->dev, "Unable to allocate RX DMA channel\n");
	} else {
		qp->tx_dma_chan = NULL;
		qp->rx_dma_chan = NULL;
	}

	qp->tx_mw_dma_addr = 0;
	if (qp->tx_dma_chan) {
		qp->tx_mw_dma_addr =
			dma_map_resource(qp->tx_dma_chan->device->dev,
					 qp->tx_mw_phys, qp->tx_mw_size,
					 DMA_FROM_DEVICE, 0);
		if (dma_mapping_error(qp->tx_dma_chan->device->dev,
				      qp->tx_mw_dma_addr)) {
			qp->tx_mw_dma_addr = 0;
			goto err1;
		}
	}

	dev_dbg(&pdev->dev, "Using %s memcpy for TX\n",
		qp->tx_dma_chan ? "DMA" : "CPU");

	dev_dbg(&pdev->dev, "Using %s memcpy for RX\n",
		qp->rx_dma_chan ? "DMA" : "CPU");

	for (i = 0; i < NTB_QP_DEF_NUM_ENTRIES; i++) {
		entry = kzalloc_node(sizeof(*entry), GFP_KERNEL, node);
		if (!entry)
			goto err1;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry,
			     &qp->rx_free_q);
	}
	qp->rx_alloc_entry = NTB_QP_DEF_NUM_ENTRIES;

	for (i = 0; i < qp->tx_max_entry; i++) {
		entry = kzalloc_node(sizeof(*entry), GFP_KERNEL, node);
		if (!entry)
			goto err2;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_tx_free_q_lock, &entry->entry,
			     &qp->tx_free_q);
	}

	ntb_db_clear(qp->ndev, qp_bit);
	ntb_db_clear_mask(qp->ndev, qp_bit);

	dev_info(&pdev->dev, "NTB Transport QP %d created\n", qp->qp_num);

	return qp;

err2:
	while ((entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q)))
		kfree(entry);
err1:
	qp->rx_alloc_entry = 0;
	while ((entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_free_q)))
		kfree(entry);
	if (qp->tx_mw_dma_addr)
		dma_unmap_resource(qp->tx_dma_chan->device->dev,
				   qp->tx_mw_dma_addr, qp->tx_mw_size,
				   DMA_FROM_DEVICE, 0);
	if (qp->tx_dma_chan)
		dma_release_channel(qp->tx_dma_chan);
	if (qp->rx_dma_chan)
		dma_release_channel(qp->rx_dma_chan);
	nt->qp_bitmap_free |= qp_bit;
err:
	return NULL;
}