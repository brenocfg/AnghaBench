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
struct omap_sham_reqctx {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct omap_sham_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FLAGS_DMA_ACTIVE ; 
 struct omap_sham_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_sham_update_dma_stop(struct omap_sham_dev *dd)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);

	dma_unmap_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE);

	clear_bit(FLAGS_DMA_ACTIVE, &dd->flags);

	return 0;
}