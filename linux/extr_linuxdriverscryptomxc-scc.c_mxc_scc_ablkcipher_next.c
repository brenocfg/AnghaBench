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
struct mxc_scc_ctx {int size; int ctrl; struct mxc_scc* scc; } ;
struct mxc_scc {int block_size_bytes; void* black_memory; void* red_memory; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct crypto_async_request {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 scalar_t__ SCC_SCM_BLACK_START ; 
 scalar_t__ SCC_SCM_CTRL ; 
 int SCC_SCM_CTRL_DECRYPT_MODE ; 
 scalar_t__ SCC_SCM_ERROR_STATUS ; 
 scalar_t__ SCC_SCM_INTR_CTRL ; 
 int SCC_SCM_INTR_CTRL_CLR_INTR ; 
 scalar_t__ SCC_SCM_LENGTH ; 
 scalar_t__ SCC_SCM_RED_START ; 
 struct ablkcipher_request* ablkcipher_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,void*,...) ; 
 int /*<<< orphan*/  mxc_scc_ablkcipher_req_complete (struct crypto_async_request*,struct mxc_scc_ctx*,int) ; 
 int mxc_scc_put_data (struct mxc_scc_ctx*,struct ablkcipher_request*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxc_scc_ablkcipher_next(struct mxc_scc_ctx *ctx,
				    struct crypto_async_request *req)
{
	struct ablkcipher_request *ablkreq = ablkcipher_request_cast(req);
	struct mxc_scc *scc = ctx->scc;
	int err;

	dev_dbg(scc->dev, "dispatch request (nbytes=%d, src=%p, dst=%p)\n",
		ablkreq->nbytes, ablkreq->src, ablkreq->dst);

	writel(0, scc->base + SCC_SCM_ERROR_STATUS);

	err = mxc_scc_put_data(ctx, ablkreq);
	if (err) {
		mxc_scc_ablkcipher_req_complete(req, ctx, err);
		return;
	}

	dev_dbg(scc->dev, "Start encryption (0x%p/0x%p)\n",
		(void *)readl(scc->base + SCC_SCM_RED_START),
		(void *)readl(scc->base + SCC_SCM_BLACK_START));

	/* clear interrupt control registers */
	writel(SCC_SCM_INTR_CTRL_CLR_INTR,
	       scc->base + SCC_SCM_INTR_CTRL);

	writel((ctx->size / ctx->scc->block_size_bytes) - 1,
	       scc->base + SCC_SCM_LENGTH);

	dev_dbg(scc->dev, "Process %d block(s) in 0x%p\n",
		ctx->size / ctx->scc->block_size_bytes,
		(ctx->ctrl & SCC_SCM_CTRL_DECRYPT_MODE) ? scc->black_memory :
		scc->red_memory);

	writel(ctx->ctrl, scc->base + SCC_SCM_CTRL);
}