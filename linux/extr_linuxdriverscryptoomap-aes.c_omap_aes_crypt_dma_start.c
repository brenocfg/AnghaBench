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
struct omap_aes_dev {int /*<<< orphan*/  out_sg_len; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  dev; int /*<<< orphan*/  in_sg_len; int /*<<< orphan*/  in_sg; int /*<<< orphan*/  pio_only; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_aes_crypt_dma (struct omap_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int omap_aes_crypt_dma_start(struct omap_aes_dev *dd)
{
	int err;

	pr_debug("total: %d\n", dd->total);

	if (!dd->pio_only) {
		err = dma_map_sg(dd->dev, dd->in_sg, dd->in_sg_len,
				 DMA_TO_DEVICE);
		if (!err) {
			dev_err(dd->dev, "dma_map_sg() error\n");
			return -EINVAL;
		}

		err = dma_map_sg(dd->dev, dd->out_sg, dd->out_sg_len,
				 DMA_FROM_DEVICE);
		if (!err) {
			dev_err(dd->dev, "dma_map_sg() error\n");
			return -EINVAL;
		}
	}

	err = omap_aes_crypt_dma(dd, dd->in_sg, dd->out_sg, dd->in_sg_len,
				 dd->out_sg_len);
	if (err && !dd->pio_only) {
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
			     DMA_FROM_DEVICE);
	}

	return err;
}