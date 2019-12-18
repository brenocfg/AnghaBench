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
struct gf100_grctx_func {int const bundle_size; } ;
struct gf100_grctx {TYPE_2__* gr; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {struct gf100_grctx_func* grctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmio_refn (struct gf100_grctx*,int,int,int const,int const) ; 
 int mmio_vram (struct gf100_grctx*,int const,int,int) ; 
 int /*<<< orphan*/  mmio_wr32 (struct gf100_grctx*,int,int) ; 

void
gf100_grctx_generate_bundle(struct gf100_grctx *info)
{
	const struct gf100_grctx_func *grctx = info->gr->func->grctx;
	const int s = 8;
	const int b = mmio_vram(info, grctx->bundle_size, (1 << s), true);
	mmio_refn(info, 0x408004, 0x00000000, s, b);
	mmio_wr32(info, 0x408008, 0x80000000 | (grctx->bundle_size >> s));
	mmio_refn(info, 0x418808, 0x00000000, s, b);
	mmio_wr32(info, 0x41880c, 0x80000000 | (grctx->bundle_size >> s));
}