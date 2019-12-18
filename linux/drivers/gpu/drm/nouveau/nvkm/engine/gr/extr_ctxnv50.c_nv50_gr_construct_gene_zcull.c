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
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  xf_emit (struct nvkm_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_gr_construct_gene_zcull(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	/* end of strand 0 on pre-NVA0, beginning of strand 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 1, 0x3f);		/* 0000003f UNK1590 */
	xf_emit(ctx, 1, 0);		/* 00000001 ALPHA_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_REF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_BACK_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 2);		/* 00000003 tesla UNK143C */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff tesla UNK0D6C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 CLIPID_ENABLE */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 4);		/* 0000000f CULL_MODE */
	xf_emit(ctx, 1, 0);		/* 0000ffff */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 00000001 POLYGON_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0);		/* 000000ff CLEAR_STENCIL */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_FRONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_REF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_FRONT_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff CLEAR_DEPTH */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 00000003 tesla UNK1108 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0x1001);	/* 00001fff ZETA_ARRAY_MODE */
	/* SEEK */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 0x10, 0);		/* 00000001 SCISSOR_ENABLE */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_RANGE_NEAR */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_RANGE_FAR */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff/3ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);		/* 00000001 VIEWPORT_CLIP_RECTS_EN */
	xf_emit(ctx, 1, 3);		/* 00000003 FP_CTRL_UNK196C */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK1968 */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 0fffffff tesla UNK1104 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK151C */
}