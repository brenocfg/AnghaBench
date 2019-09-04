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
typedef  int u32 ;
struct gf100_grctx_func {int bundle_size; int bundle_token_limit; int /*<<< orphan*/  bundle_min_gpm_fifo_depth; } ;
struct gf100_grctx {TYPE_1__* gr; } ;
struct TYPE_4__ {struct gf100_grctx_func* grctx; } ;
struct TYPE_3__ {TYPE_2__* func; } ;

/* Variables and functions */
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmio_refn (struct gf100_grctx*,int,int,int const,int const) ; 
 int mmio_vram (struct gf100_grctx*,int,int,int) ; 
 int /*<<< orphan*/  mmio_wr32 (struct gf100_grctx*,int,int const) ; 

void
gk104_grctx_generate_bundle(struct gf100_grctx *info)
{
	const struct gf100_grctx_func *grctx = info->gr->func->grctx;
	const u32 state_limit = min(grctx->bundle_min_gpm_fifo_depth,
				    grctx->bundle_size / 0x20);
	const u32 token_limit = grctx->bundle_token_limit;
	const int s = 8;
	const int b = mmio_vram(info, grctx->bundle_size, (1 << s), true);
	mmio_refn(info, 0x408004, 0x00000000, s, b);
	mmio_wr32(info, 0x408008, 0x80000000 | (grctx->bundle_size >> s));
	mmio_refn(info, 0x418808, 0x00000000, s, b);
	mmio_wr32(info, 0x41880c, 0x80000000 | (grctx->bundle_size >> s));
	mmio_wr32(info, 0x4064c8, (state_limit << 16) | token_limit);
}