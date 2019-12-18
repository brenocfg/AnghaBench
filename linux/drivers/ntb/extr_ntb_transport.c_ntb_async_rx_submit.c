#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ntb_transport_qp {int /*<<< orphan*/  rx_async; int /*<<< orphan*/  last_cookie; struct dma_chan* rx_dma_chan; } ;
struct ntb_queue_entry {size_t len; void* buf; struct ntb_transport_qp* qp; } ;
struct dmaengine_unmap_data {size_t len; int to_cnt; int from_cnt; void** addr; } ;
struct dma_device {struct dma_async_tx_descriptor* (* device_prep_dma_memcpy ) (struct dma_chan*,void*,void*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;
struct dma_chan {struct dma_device* device; } ;
struct dma_async_tx_descriptor {struct ntb_queue_entry* callback_param; int /*<<< orphan*/  callback_result; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 size_t PAGE_MASK ; 
 void* dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_set_unmap (struct dma_async_tx_descriptor*,struct dmaengine_unmap_data*) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dmaengine_unmap_data* dmaengine_get_unmap_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_unmap_put (struct dmaengine_unmap_data*) ; 
 int /*<<< orphan*/  is_dma_copy_aligned (struct dma_device*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  ntb_rx_copy_callback ; 
 struct dma_async_tx_descriptor* stub1 (struct dma_chan*,void*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int ntb_async_rx_submit(struct ntb_queue_entry *entry, void *offset)
{
	struct dma_async_tx_descriptor *txd;
	struct ntb_transport_qp *qp = entry->qp;
	struct dma_chan *chan = qp->rx_dma_chan;
	struct dma_device *device;
	size_t pay_off, buff_off, len;
	struct dmaengine_unmap_data *unmap;
	dma_cookie_t cookie;
	void *buf = entry->buf;

	len = entry->len;
	device = chan->device;
	pay_off = (size_t)offset & ~PAGE_MASK;
	buff_off = (size_t)buf & ~PAGE_MASK;

	if (!is_dma_copy_aligned(device, pay_off, buff_off, len))
		goto err;

	unmap = dmaengine_get_unmap_data(device->dev, 2, GFP_NOWAIT);
	if (!unmap)
		goto err;

	unmap->len = len;
	unmap->addr[0] = dma_map_page(device->dev, virt_to_page(offset),
				      pay_off, len, DMA_TO_DEVICE);
	if (dma_mapping_error(device->dev, unmap->addr[0]))
		goto err_get_unmap;

	unmap->to_cnt = 1;

	unmap->addr[1] = dma_map_page(device->dev, virt_to_page(buf),
				      buff_off, len, DMA_FROM_DEVICE);
	if (dma_mapping_error(device->dev, unmap->addr[1]))
		goto err_get_unmap;

	unmap->from_cnt = 1;

	txd = device->device_prep_dma_memcpy(chan, unmap->addr[1],
					     unmap->addr[0], len,
					     DMA_PREP_INTERRUPT);
	if (!txd)
		goto err_get_unmap;

	txd->callback_result = ntb_rx_copy_callback;
	txd->callback_param = entry;
	dma_set_unmap(txd, unmap);

	cookie = dmaengine_submit(txd);
	if (dma_submit_error(cookie))
		goto err_set_unmap;

	dmaengine_unmap_put(unmap);

	qp->last_cookie = cookie;

	qp->rx_async++;

	return 0;

err_set_unmap:
	dmaengine_unmap_put(unmap);
err_get_unmap:
	dmaengine_unmap_put(unmap);
err:
	return -ENXIO;
}