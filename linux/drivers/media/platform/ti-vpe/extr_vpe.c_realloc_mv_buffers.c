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
struct vpe_ctx {size_t mv_buf_size; scalar_t__ src_mv_buf_selector; int /*<<< orphan*/ * mv_buf_dma; void** mv_buf; TYPE_2__* dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_err (TYPE_2__*,char*) ; 

__attribute__((used)) static int realloc_mv_buffers(struct vpe_ctx *ctx, size_t size)
{
	struct device *dev = ctx->dev->v4l2_dev.dev;

	if (ctx->mv_buf_size == size)
		return 0;

	if (ctx->mv_buf[0])
		dma_free_coherent(dev, ctx->mv_buf_size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

	if (ctx->mv_buf[1])
		dma_free_coherent(dev, ctx->mv_buf_size, ctx->mv_buf[1],
			ctx->mv_buf_dma[1]);

	if (size == 0)
		return 0;

	ctx->mv_buf[0] = dma_alloc_coherent(dev, size, &ctx->mv_buf_dma[0],
				GFP_KERNEL);
	if (!ctx->mv_buf[0]) {
		vpe_err(ctx->dev, "failed to allocate motion vector buffer\n");
		return -ENOMEM;
	}

	ctx->mv_buf[1] = dma_alloc_coherent(dev, size, &ctx->mv_buf_dma[1],
				GFP_KERNEL);
	if (!ctx->mv_buf[1]) {
		vpe_err(ctx->dev, "failed to allocate motion vector buffer\n");
		dma_free_coherent(dev, size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

		return -ENOMEM;
	}

	ctx->mv_buf_size = size;
	ctx->src_mv_buf_selector = 0;

	return 0;
}