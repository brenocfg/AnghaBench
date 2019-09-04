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
struct device {int dummy; } ;
struct caam_rng_ctx {int /*<<< orphan*/ * bufs; int /*<<< orphan*/  sh_desc; int /*<<< orphan*/  sh_desc_dma; struct device* jrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_unmap_buf (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rng_unmap_ctx(struct caam_rng_ctx *ctx)
{
	struct device *jrdev = ctx->jrdev;

	if (ctx->sh_desc_dma)
		dma_unmap_single(jrdev, ctx->sh_desc_dma,
				 desc_bytes(ctx->sh_desc), DMA_TO_DEVICE);
	rng_unmap_buf(jrdev, &ctx->bufs[0]);
	rng_unmap_buf(jrdev, &ctx->bufs[1]);
}