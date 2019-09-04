#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zstd_ctx {int /*<<< orphan*/  cwksp; int /*<<< orphan*/  cctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t ZSTD_CCtxWorkspaceBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_initCCtx (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (size_t const) ; 
 TYPE_1__ zstd_params () ; 

__attribute__((used)) static int zstd_comp_init(struct zstd_ctx *ctx)
{
	int ret = 0;
	const ZSTD_parameters params = zstd_params();
	const size_t wksp_size = ZSTD_CCtxWorkspaceBound(params.cParams);

	ctx->cwksp = vzalloc(wksp_size);
	if (!ctx->cwksp) {
		ret = -ENOMEM;
		goto out;
	}

	ctx->cctx = ZSTD_initCCtx(ctx->cwksp, wksp_size);
	if (!ctx->cctx) {
		ret = -EINVAL;
		goto out_free;
	}
out:
	return ret;
out_free:
	vfree(ctx->cwksp);
	goto out;
}