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
struct nvkm_grctx {struct nvkm_device* device; } ;
struct nvkm_device {int /*<<< orphan*/  chipset; } ;

/* Variables and functions */
 scalar_t__ IS_NVA3F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xf_emit (struct nvkm_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_gr_construct_gene_ropm2(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUERY */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 2, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 000000ff QUERY_ADDRESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUERY_ADDRESS_LOW, COUNTER */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 7 */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUERY */
	xf_emit(ctx, 1, 0);		/* 000000ff QUERY_ADDRESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUERY_ADDRESS_LOW, COUNTER */
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x4e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 0);		/* 00000001 eng2d UNK260 */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0x11);	/* 000000ff tesla UNK1968 */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
}