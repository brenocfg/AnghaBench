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
struct nvkm_grctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xf_emit (struct nvkm_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_gr_construct_gene_clipid(struct nvkm_grctx *ctx)
{
	/* middle of strand 0 on pre-NVA0 [after 24xx], middle of area 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000007 UNK0FB4 */
	/* SEEK */
	xf_emit(ctx, 4, 0);		/* 07ffffff CLIPID_REGION_HORIZ */
	xf_emit(ctx, 4, 0);		/* 07ffffff CLIPID_REGION_VERT */
	xf_emit(ctx, 2, 0);		/* 07ffffff SCREEN_SCISSOR */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff UNK1508 */
	xf_emit(ctx, 1, 0);		/* 00000001 CLIPID_ENABLE */
	xf_emit(ctx, 1, 0x80);		/* 00003fff CLIPID_WIDTH */
	xf_emit(ctx, 1, 0);		/* 000000ff CLIPID_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff CLIPID_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff CLIPID_ADDRESS_LOW */
	xf_emit(ctx, 1, 0x80);		/* 00003fff CLIPID_HEIGHT */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_CLIPID */
}