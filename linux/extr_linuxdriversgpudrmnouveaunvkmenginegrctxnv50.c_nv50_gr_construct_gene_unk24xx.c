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
nv50_gr_construct_gene_unk24xx(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	int i;
	/* middle of strand 0 on pre-NVA0 [after m2mf], end of strand 2 on NVAx */
	/* SEEK */
	xf_emit(ctx, 0x33, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 4, 0);	/* RO */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 9, 0);	/* ffffffff, 7ff */

		xf_emit(ctx, 4, 0);	/* RO */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 9, 0);	/* ffffffff, 7ff */
	} else {
		xf_emit(ctx, 0xc, 0);	/* RO */
		/* SEEK */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */

		/* SEEK */
		xf_emit(ctx, 0xc, 0);	/* RO */
		/* SEEK */
		xf_emit(ctx, 0xe10, 0); /* 190 * 9: 8*ffffffff, 7ff */
		xf_emit(ctx, 1, 0);	/* 1ff */
		xf_emit(ctx, 8, 0);	/* 0? */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 3);	/* 00000003 tesla UNK1100 */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUILTIN_ATTR_EN */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COLOR */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	/* SEEK */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 2, 4);	/* 000000ff */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COLOR */
	xf_emit(ctx, 1, 0);		/* 00000001 VERTEX_TWO_SIDE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPRITE_ENABLE */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 0x27);		/* 000000ff SEMANTIC_PRIM_ID */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	for (i = 0; i < 10; i++) {
		/* SEEK */
		xf_emit(ctx, 0x40, 0);		/* ffffffff */
		xf_emit(ctx, 0x10, 0);		/* 3, 0, 0.... */
		xf_emit(ctx, 0x10, 0);		/* ffffffff */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPRITE_CTRL */
	xf_emit(ctx, 1, 1);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff NOPERSPECTIVE_BITMAP */
	xf_emit(ctx, 0x10, 0);		/* 00ffffff POINT_COORD_REPLACE_MAP */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_ORIGIN */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 000003ff */
}