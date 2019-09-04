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
struct atmel_tdes_dev {int buflen; void* buf_in; void* buf_out; void* dma_addr_in; int /*<<< orphan*/  dev; void* dma_addr_out; } ;

/* Variables and functions */
 int DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 void* dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int atmel_tdes_buff_init(struct atmel_tdes_dev *dd)
{
	int err = -ENOMEM;

	dd->buf_in = (void *)__get_free_pages(GFP_KERNEL, 0);
	dd->buf_out = (void *)__get_free_pages(GFP_KERNEL, 0);
	dd->buflen = PAGE_SIZE;
	dd->buflen &= ~(DES_BLOCK_SIZE - 1);

	if (!dd->buf_in || !dd->buf_out) {
		dev_err(dd->dev, "unable to alloc pages.\n");
		goto err_alloc;
	}

	/* MAP here */
	dd->dma_addr_in = dma_map_single(dd->dev, dd->buf_in,
					dd->buflen, DMA_TO_DEVICE);
	if (dma_mapping_error(dd->dev, dd->dma_addr_in)) {
		dev_err(dd->dev, "dma %zd bytes error\n", dd->buflen);
		err = -EINVAL;
		goto err_map_in;
	}

	dd->dma_addr_out = dma_map_single(dd->dev, dd->buf_out,
					dd->buflen, DMA_FROM_DEVICE);
	if (dma_mapping_error(dd->dev, dd->dma_addr_out)) {
		dev_err(dd->dev, "dma %zd bytes error\n", dd->buflen);
		err = -EINVAL;
		goto err_map_out;
	}

	return 0;

err_map_out:
	dma_unmap_single(dd->dev, dd->dma_addr_in, dd->buflen,
		DMA_TO_DEVICE);
err_map_in:
err_alloc:
	free_page((unsigned long)dd->buf_out);
	free_page((unsigned long)dd->buf_in);
	if (err)
		pr_err("error: %d\n", err);
	return err;
}