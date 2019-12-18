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
 scalar_t__ IS_NVA3F (int) ; 
 int /*<<< orphan*/  xf_emit (struct nvkm_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_gr_construct_gene_unk14xx(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	/* middle of area 2 on pre-NVA0, beginning of area 2 on NVA0, area 7 on >NVA0 */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 5, 0);		/* ffffffff */
		xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COLOR */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 1, 0);		/* 000003ff */
		xf_emit(ctx, 1, 0x804);		/* 00000fff SEMANTIC_CLIP */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 2, 4);		/* 7f, ff */
		xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	}
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x10);			/* 7f/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);			/* 000000ff VP_CLIP_DISTANCE_ENABLE */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);		/* 3ff */
	xf_emit(ctx, 1, 0);			/* 000000ff tesla UNK1940 */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK0D7C */
	xf_emit(ctx, 1, 0x804);			/* 00000fff SEMANTIC_CLIP */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPORT_TRANSFORM_EN */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POLYGON_MODE */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0x7f);		/* 000000ff tesla UNK0FFC */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 SHADE_MODEL */
	xf_emit(ctx, 1, 0x80c14);		/* 01ffffff SEMANTIC_COLOR */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0x8100c12);		/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x10);			/* 7f/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK0D7C */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK0F8C */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPORT_TRANSFORM_EN */
	xf_emit(ctx, 1, 0x8100c12);		/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 4, 0);			/* ffffffff NOPERSPECTIVE_BITMAP */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0);			/* 0000000f */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);		/* 000003ff tesla UNK0D68 */
	else
		xf_emit(ctx, 1, 0x7ff);		/* 000007ff tesla UNK0D68 */
	xf_emit(ctx, 1, 0x80c14);		/* 01ffffff SEMANTIC_COLOR */
	xf_emit(ctx, 1, 0);			/* 00000001 VERTEX_TWO_SIDE_ENABLE */
	xf_emit(ctx, 0x30, 0);			/* ffffffff VIEWPORT_SCALE: X0, Y0, Z0, X1, Y1, ... */
	xf_emit(ctx, 3, 0);			/* f, 0, 0 */
	xf_emit(ctx, 3, 0);			/* ffffffff last VIEWPORT_SCALE? */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 1);			/* 00000001 VIEWPORT_TRANSFORM_EN */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1924 */
	xf_emit(ctx, 1, 0x10);			/* 000000ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);			/* 00000001 */
	xf_emit(ctx, 0x30, 0);			/* ffffffff VIEWPORT_TRANSLATE */
	xf_emit(ctx, 3, 0);			/* f, 0, 0 */
	xf_emit(ctx, 3, 0);			/* ffffffff */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 2, 0x88);			/* 000001ff tesla UNK19D8 */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1924 */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 4);			/* 0000000f CULL_MODE */
	xf_emit(ctx, 2, 0);			/* 07ffffff SCREEN_SCISSOR */
	xf_emit(ctx, 2, 0);			/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0);			/* 00000003 WINDOW_ORIGIN */
	xf_emit(ctx, 0x10, 0);			/* 00000001 SCISSOR_ENABLE */
	xf_emit(ctx, 1, 0);			/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0x26);			/* 000000ff SEMANTIC_LAYER */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0);			/* 0000000f */
	xf_emit(ctx, 1, 0x3f800000);		/* ffffffff LINE_WIDTH */
	xf_emit(ctx, 1, 0);			/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0);			/* 00000001 LINE_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);			/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POLYGON_MODE */
	xf_emit(ctx, 1, 0x10);			/* 000000ff VIEW_VOLUME_CLIP_CTRL */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);		/* ffffffff */
		xf_emit(ctx, 1, 0);		/* 00000001 */
		xf_emit(ctx, 1, 0);		/* 000003ff */
	}
	xf_emit(ctx, 0x20, 0);			/* 10xbits ffffffff, 3fffff. SCISSOR_* */
	xf_emit(ctx, 1, 0);			/* f */
	xf_emit(ctx, 1, 0);			/* 0? */
	xf_emit(ctx, 1, 0);			/* ffffffff */
	xf_emit(ctx, 1, 0);			/* 003fffff */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0x52);			/* 000001ff SEMANTIC_PTSZ */
	xf_emit(ctx, 1, 0);			/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0x26);			/* 000000ff SEMANTIC_LAYER */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 4);			/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);			/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);			/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x1a);			/* 0000001f POLYGON_MODE */
	xf_emit(ctx, 1, 0);			/* 00000001 LINE_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);			/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0x00ffff00);		/* 00ffffff LINE_STIPPLE_PATTERN */
	xf_emit(ctx, 1, 0);			/* 0000000f */
}