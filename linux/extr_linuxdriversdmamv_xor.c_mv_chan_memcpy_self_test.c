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
typedef  scalar_t__ u8 ;
struct dma_chan {TYPE_1__* device; } ;
struct mv_xor_chan {struct dma_chan dmachan; } ;
struct dmaengine_unmap_data {int to_cnt; int from_cnt; int len; void** addr; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_COMPLETE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 struct dmaengine_unmap_data* dmaengine_get_unmap_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_unmap_put (struct dmaengine_unmap_data*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,void*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mv_xor_alloc_chan_resources (struct dma_chan*) ; 
 int /*<<< orphan*/  mv_xor_free_chan_resources (struct dma_chan*) ; 
 int /*<<< orphan*/  mv_xor_issue_pending (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* mv_xor_prep_dma_memcpy (struct dma_chan*,void*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_xor_status (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_xor_tx_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int mv_chan_memcpy_self_test(struct mv_xor_chan *mv_chan)
{
	int i, ret;
	void *src, *dest;
	dma_addr_t src_dma, dest_dma;
	struct dma_chan *dma_chan;
	dma_cookie_t cookie;
	struct dma_async_tx_descriptor *tx;
	struct dmaengine_unmap_data *unmap;
	int err = 0;

	src = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!src)
		return -ENOMEM;

	dest = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!dest) {
		kfree(src);
		return -ENOMEM;
	}

	/* Fill in src buffer */
	for (i = 0; i < PAGE_SIZE; i++)
		((u8 *) src)[i] = (u8)i;

	dma_chan = &mv_chan->dmachan;
	if (mv_xor_alloc_chan_resources(dma_chan) < 1) {
		err = -ENODEV;
		goto out;
	}

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, 2, GFP_KERNEL);
	if (!unmap) {
		err = -ENOMEM;
		goto free_resources;
	}

	src_dma = dma_map_page(dma_chan->device->dev, virt_to_page(src),
			       offset_in_page(src), PAGE_SIZE,
			       DMA_TO_DEVICE);
	unmap->addr[0] = src_dma;

	ret = dma_mapping_error(dma_chan->device->dev, src_dma);
	if (ret) {
		err = -ENOMEM;
		goto free_resources;
	}
	unmap->to_cnt = 1;

	dest_dma = dma_map_page(dma_chan->device->dev, virt_to_page(dest),
				offset_in_page(dest), PAGE_SIZE,
				DMA_FROM_DEVICE);
	unmap->addr[1] = dest_dma;

	ret = dma_mapping_error(dma_chan->device->dev, dest_dma);
	if (ret) {
		err = -ENOMEM;
		goto free_resources;
	}
	unmap->from_cnt = 1;
	unmap->len = PAGE_SIZE;

	tx = mv_xor_prep_dma_memcpy(dma_chan, dest_dma, src_dma,
				    PAGE_SIZE, 0);
	if (!tx) {
		dev_err(dma_chan->device->dev,
			"Self-test cannot prepare operation, disabling\n");
		err = -ENODEV;
		goto free_resources;
	}

	cookie = mv_xor_tx_submit(tx);
	if (dma_submit_error(cookie)) {
		dev_err(dma_chan->device->dev,
			"Self-test submit error, disabling\n");
		err = -ENODEV;
		goto free_resources;
	}

	mv_xor_issue_pending(dma_chan);
	async_tx_ack(tx);
	msleep(1);

	if (mv_xor_status(dma_chan, cookie, NULL) !=
	    DMA_COMPLETE) {
		dev_err(dma_chan->device->dev,
			"Self-test copy timed out, disabling\n");
		err = -ENODEV;
		goto free_resources;
	}

	dma_sync_single_for_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FROM_DEVICE);
	if (memcmp(src, dest, PAGE_SIZE)) {
		dev_err(dma_chan->device->dev,
			"Self-test copy failed compare, disabling\n");
		err = -ENODEV;
		goto free_resources;
	}

free_resources:
	dmaengine_unmap_put(unmap);
	mv_xor_free_chan_resources(dma_chan);
out:
	kfree(src);
	kfree(dest);
	return err;
}