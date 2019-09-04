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
typedef  int u8 ;
typedef  int u32 ;
struct page {int dummy; } ;
struct dma_chan {TYPE_1__* device; } ;
struct mv_xor_chan {struct dma_chan dmachan; } ;
struct dmaengine_unmap_data {int from_cnt; int len; void** addr; int /*<<< orphan*/  to_cnt; } ;
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
 int MV_XOR_NUM_SRC_TEST ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 void* dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 struct dmaengine_unmap_data* dmaengine_get_unmap_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_unmap_put (struct dmaengine_unmap_data*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mv_xor_alloc_chan_resources (struct dma_chan*) ; 
 int /*<<< orphan*/  mv_xor_free_chan_resources (struct dma_chan*) ; 
 int /*<<< orphan*/  mv_xor_issue_pending (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* mv_xor_prep_dma_xor (struct dma_chan*,void*,void**,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_xor_status (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_xor_tx_submit (struct dma_async_tx_descriptor*) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static int
mv_chan_xor_self_test(struct mv_xor_chan *mv_chan)
{
	int i, src_idx, ret;
	struct page *dest;
	struct page *xor_srcs[MV_XOR_NUM_SRC_TEST];
	dma_addr_t dma_srcs[MV_XOR_NUM_SRC_TEST];
	dma_addr_t dest_dma;
	struct dma_async_tx_descriptor *tx;
	struct dmaengine_unmap_data *unmap;
	struct dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_word;
	int err = 0;
	int src_count = MV_XOR_NUM_SRC_TEST;

	for (src_idx = 0; src_idx < src_count; src_idx++) {
		xor_srcs[src_idx] = alloc_page(GFP_KERNEL);
		if (!xor_srcs[src_idx]) {
			while (src_idx--)
				__free_page(xor_srcs[src_idx]);
			return -ENOMEM;
		}
	}

	dest = alloc_page(GFP_KERNEL);
	if (!dest) {
		while (src_idx--)
			__free_page(xor_srcs[src_idx]);
		return -ENOMEM;
	}

	/* Fill in src buffers */
	for (src_idx = 0; src_idx < src_count; src_idx++) {
		u8 *ptr = page_address(xor_srcs[src_idx]);
		for (i = 0; i < PAGE_SIZE; i++)
			ptr[i] = (1 << src_idx);
	}

	for (src_idx = 0; src_idx < src_count; src_idx++)
		cmp_byte ^= (u8) (1 << src_idx);

	cmp_word = (cmp_byte << 24) | (cmp_byte << 16) |
		(cmp_byte << 8) | cmp_byte;

	memset(page_address(dest), 0, PAGE_SIZE);

	dma_chan = &mv_chan->dmachan;
	if (mv_xor_alloc_chan_resources(dma_chan) < 1) {
		err = -ENODEV;
		goto out;
	}

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, src_count + 1,
					 GFP_KERNEL);
	if (!unmap) {
		err = -ENOMEM;
		goto free_resources;
	}

	/* test xor */
	for (i = 0; i < src_count; i++) {
		unmap->addr[i] = dma_map_page(dma_chan->device->dev, xor_srcs[i],
					      0, PAGE_SIZE, DMA_TO_DEVICE);
		dma_srcs[i] = unmap->addr[i];
		ret = dma_mapping_error(dma_chan->device->dev, unmap->addr[i]);
		if (ret) {
			err = -ENOMEM;
			goto free_resources;
		}
		unmap->to_cnt++;
	}

	unmap->addr[src_count] = dma_map_page(dma_chan->device->dev, dest, 0, PAGE_SIZE,
				      DMA_FROM_DEVICE);
	dest_dma = unmap->addr[src_count];
	ret = dma_mapping_error(dma_chan->device->dev, unmap->addr[src_count]);
	if (ret) {
		err = -ENOMEM;
		goto free_resources;
	}
	unmap->from_cnt = 1;
	unmap->len = PAGE_SIZE;

	tx = mv_xor_prep_dma_xor(dma_chan, dest_dma, dma_srcs,
				 src_count, PAGE_SIZE, 0);
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
	msleep(8);

	if (mv_xor_status(dma_chan, cookie, NULL) !=
	    DMA_COMPLETE) {
		dev_err(dma_chan->device->dev,
			"Self-test xor timed out, disabling\n");
		err = -ENODEV;
		goto free_resources;
	}

	dma_sync_single_for_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FROM_DEVICE);
	for (i = 0; i < (PAGE_SIZE / sizeof(u32)); i++) {
		u32 *ptr = page_address(dest);
		if (ptr[i] != cmp_word) {
			dev_err(dma_chan->device->dev,
				"Self-test xor failed compare, disabling. index %d, data %x, expected %x\n",
				i, ptr[i], cmp_word);
			err = -ENODEV;
			goto free_resources;
		}
	}

free_resources:
	dmaengine_unmap_put(unmap);
	mv_xor_free_chan_resources(dma_chan);
out:
	src_idx = src_count;
	while (src_idx--)
		__free_page(xor_srcs[src_idx]);
	__free_page(dest);
	return err;
}