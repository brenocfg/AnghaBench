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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_grctx {scalar_t__ mode; int ctxvals_pos; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ NVKM_GRCTX_VALS ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dd_emit(struct nvkm_grctx *ctx, int num, u32 val) {
	int i;
	if (val && ctx->mode == NVKM_GRCTX_VALS) {
		for (i = 0; i < num; i++)
			nvkm_wo32(ctx->data, 4 * (ctx->ctxvals_pos + i), val);
	}
	ctx->ctxvals_pos += num;
}