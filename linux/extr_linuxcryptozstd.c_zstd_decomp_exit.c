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
struct zstd_ctx {int /*<<< orphan*/ * dctx; int /*<<< orphan*/ * dwksp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zstd_decomp_exit(struct zstd_ctx *ctx)
{
	vfree(ctx->dwksp);
	ctx->dwksp = NULL;
	ctx->dctx = NULL;
}