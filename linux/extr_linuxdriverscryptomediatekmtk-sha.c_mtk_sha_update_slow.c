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
typedef  int u32 ;
struct mtk_sha_reqctx {int flags; size_t bufcnt; scalar_t__ total; } ;
struct mtk_sha_rec {int /*<<< orphan*/  flags; int /*<<< orphan*/  req; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t SHA_BUF_SIZE ; 
 int /*<<< orphan*/  SHA_FLAGS_FINAL ; 
 int SHA_FLAGS_FINUP ; 
 struct mtk_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  mtk_sha_append_sg (struct mtk_sha_reqctx*) ; 
 int mtk_sha_dma_map (struct mtk_cryp*,struct mtk_sha_rec*,struct mtk_sha_reqctx*,size_t) ; 
 int /*<<< orphan*/  mtk_sha_fill_padding (struct mtk_sha_reqctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_sha_update_slow(struct mtk_cryp *cryp,
			       struct mtk_sha_rec *sha)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(sha->req);
	size_t count;
	u32 final;

	mtk_sha_append_sg(ctx);

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	dev_dbg(cryp->dev, "slow: bufcnt: %zu\n", ctx->bufcnt);

	if (final) {
		sha->flags |= SHA_FLAGS_FINAL;
		mtk_sha_fill_padding(ctx, 0);
	}

	if (final || (ctx->bufcnt == SHA_BUF_SIZE && ctx->total)) {
		count = ctx->bufcnt;
		ctx->bufcnt = 0;

		return mtk_sha_dma_map(cryp, sha, ctx, count);
	}
	return 0;
}