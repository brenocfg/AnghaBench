#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gf100_grctx_func {int attrib_nr; int attrib_nr_max; int alpha_nr_max; } ;
struct gf100_grctx {struct gf100_gr* gr; } ;
struct gf100_gr {int const tpc_total; int gpc_nr; int* tpc_nr; TYPE_1__* func; } ;
struct TYPE_2__ {struct gf100_grctx_func* grctx; } ;

/* Variables and functions */
 int TPC_UNIT (int,int,int) ; 
 int /*<<< orphan*/  mmio_refn (struct gf100_grctx*,int,int,int const,int const) ; 
 int /*<<< orphan*/  mmio_skip (struct gf100_grctx*,int const,int const) ; 
 int mmio_vram (struct gf100_grctx*,int const,int,int) ; 
 int /*<<< orphan*/  mmio_wr32 (struct gf100_grctx*,int const,int const) ; 

void
gf100_grctx_generate_attrib(struct gf100_grctx *info)
{
	struct gf100_gr *gr = info->gr;
	const struct gf100_grctx_func *grctx = gr->func->grctx;
	const u32 attrib = grctx->attrib_nr;
	const u32   size = 0x20 * (grctx->attrib_nr_max + grctx->alpha_nr_max);
	const int s = 12;
	const int b = mmio_vram(info, size * gr->tpc_total, (1 << s), false);
	int gpc, tpc;
	u32 bo = 0;

	mmio_refn(info, 0x418810, 0x80000000, s, b);
	mmio_refn(info, 0x419848, 0x10000000, s, b);
	mmio_wr32(info, 0x405830, (attrib << 16));

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		for (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++) {
			const u32 o = TPC_UNIT(gpc, tpc, 0x0520);
			mmio_skip(info, o, (attrib << 16) | ++bo);
			mmio_wr32(info, o, (attrib << 16) | --bo);
			bo += grctx->attrib_nr_max;
		}
	}
}