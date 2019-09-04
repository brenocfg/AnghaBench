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
struct mtk_sha_reqctx {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  buffer; } ;
struct mtk_sha_rec {int dummy; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SHA_BUF_SIZE ; 
 int /*<<< orphan*/  SHA_FLAGS_SG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_sha_xmit (struct mtk_cryp*,struct mtk_sha_rec*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_sha_dma_map(struct mtk_cryp *cryp,
			   struct mtk_sha_rec *sha,
			   struct mtk_sha_reqctx *ctx,
			   size_t count)
{
	ctx->dma_addr = dma_map_single(cryp->dev, ctx->buffer,
				       SHA_BUF_SIZE, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(cryp->dev, ctx->dma_addr))) {
		dev_err(cryp->dev, "dma map error\n");
		return -EINVAL;
	}

	ctx->flags &= ~SHA_FLAGS_SG;

	return mtk_sha_xmit(cryp, sha, ctx->dma_addr, count, 0, 0);
}