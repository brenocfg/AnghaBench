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
struct omap_des_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  total_save; int /*<<< orphan*/ * orig_out; int /*<<< orphan*/  out_sgl; int /*<<< orphan*/  in_sgl; int /*<<< orphan*/  out_sg_len; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  dev; int /*<<< orphan*/  in_sg_len; int /*<<< orphan*/  in_sg; int /*<<< orphan*/  pio_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FLAGS_IN_DATA_ST_SHIFT ; 
 int /*<<< orphan*/  FLAGS_OUT_DATA_ST_SHIFT ; 
 int /*<<< orphan*/  dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_crypto_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_des_crypt_dma_stop (struct omap_des_dev*) ; 
 int /*<<< orphan*/  omap_des_finish_req (struct omap_des_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void omap_des_done_task(unsigned long data)
{
	struct omap_des_dev *dd = (struct omap_des_dev *)data;

	pr_debug("enter done_task\n");

	if (!dd->pio_only) {
		dma_sync_sg_for_device(dd->dev, dd->out_sg, dd->out_sg_len,
				       DMA_FROM_DEVICE);
		dma_unmap_sg(dd->dev, dd->in_sg, dd->in_sg_len, DMA_TO_DEVICE);
		dma_unmap_sg(dd->dev, dd->out_sg, dd->out_sg_len,
			     DMA_FROM_DEVICE);
		omap_des_crypt_dma_stop(dd);
	}

	omap_crypto_cleanup(&dd->in_sgl, NULL, 0, dd->total_save,
			    FLAGS_IN_DATA_ST_SHIFT, dd->flags);

	omap_crypto_cleanup(&dd->out_sgl, dd->orig_out, 0, dd->total_save,
			    FLAGS_OUT_DATA_ST_SHIFT, dd->flags);

	omap_des_finish_req(dd, 0);

	pr_debug("exit\n");
}