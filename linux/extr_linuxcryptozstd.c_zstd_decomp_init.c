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
struct zstd_ctx {int /*<<< orphan*/  dwksp; int /*<<< orphan*/  dctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t ZSTD_DCtxWorkspaceBound () ; 
 int /*<<< orphan*/  ZSTD_initDCtx (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (size_t const) ; 

__attribute__((used)) static int zstd_decomp_init(struct zstd_ctx *ctx)
{
	int ret = 0;
	const size_t wksp_size = ZSTD_DCtxWorkspaceBound();

	ctx->dwksp = vzalloc(wksp_size);
	if (!ctx->dwksp) {
		ret = -ENOMEM;
		goto out;
	}

	ctx->dctx = ZSTD_initDCtx(ctx->dwksp, wksp_size);
	if (!ctx->dctx) {
		ret = -EINVAL;
		goto out_free;
	}
out:
	return ret;
out_free:
	vfree(ctx->dwksp);
	goto out;
}