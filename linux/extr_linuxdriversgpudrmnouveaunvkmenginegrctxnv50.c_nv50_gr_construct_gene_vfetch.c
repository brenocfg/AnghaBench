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
nv50_gr_construct_gene_vfetch(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	int acnt = 0x10, rep, i;
	/* beginning of strand 1 on pre-NVA0, strand 3 on NVAx */
	if (IS_NVA3F(device->chipset))
		acnt = 0x20;
	/* SEEK */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 0);	/* ffffffff tesla UNK13A4 */
		xf_emit(ctx, 1, 1);	/* 00000fff tesla UNK1318 */
	}
	xf_emit(ctx, 1, 0);		/* ffffffff VERTEX_BUFFER_FIRST */
	xf_emit(ctx, 1, 0);		/* 00000001 PRIMITIVE_RESTART_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0DE8 */
	xf_emit(ctx, 1, 0);		/* ffffffff PRIMITIVE_RESTART_INDEX */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, acnt/8, 0);	/* ffffffff VTX_ATR_MASK_UNK0DD0 */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUILTIN_ATTR_EN */
	xf_emit(ctx, 1, 0x20);		/* 0000ffff tesla UNK129C */
	xf_emit(ctx, 1, 0);		/* 000000ff turing UNK370??? */
	xf_emit(ctx, 1, 0);		/* 0000ffff turing USER_PARAM_COUNT */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0xb, 0);	/* RO */
	else if (device->chipset >= 0xa0)
		xf_emit(ctx, 0x9, 0);	/* RO */
	else
		xf_emit(ctx, 0x8, 0);	/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 00000001 EDGE_FLAG */
	xf_emit(ctx, 1, 0);		/* 00000001 PROVOKING_VERTEX_LAST */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POLYGON_MODE */
	/* SEEK */
	xf_emit(ctx, 0xc, 0);		/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 7f/ff */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUILTIN_ATTR_EN */
	xf_emit(ctx, 1, 4);		/* 000001ff UNK1A28 */
	xf_emit(ctx, 1, 8);		/* 000001ff UNK0DF0 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);	/* 3ff tesla UNK0D68 */
	else
		xf_emit(ctx, 1, 0x7ff);	/* 7ff tesla UNK0D68 */
	if (device->chipset == 0xa8)
		xf_emit(ctx, 1, 0x1e00);	/* 7fff */
	/* SEEK */
	xf_emit(ctx, 0xc, 0);		/* RO or close */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUILTIN_ATTR_EN */
	if (device->chipset > 0x50 && device->chipset < 0xa0)
		xf_emit(ctx, 2, 0);	/* ffffffff */
	else
		xf_emit(ctx, 1, 0);	/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK0FD8 */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 0x10, 0);	/* 0? */
		xf_emit(ctx, 2, 0);	/* weird... */
		xf_emit(ctx, 2, 0);	/* RO */
	} else {
		xf_emit(ctx, 8, 0);	/* 0? */
		xf_emit(ctx, 1, 0);	/* weird... */
		xf_emit(ctx, 2, 0);	/* RO */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff VB_ELEMENT_BASE */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK1438 */
	xf_emit(ctx, acnt, 0);		/* 1 tesla UNK1000 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0);	/* ffffffff tesla UNK1118? */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VERTEX_ARRAY_UNK90C */
	xf_emit(ctx, 1, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VERTEX_ARRAY_UNK90C */
	xf_emit(ctx, 1, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* RO */
	xf_emit(ctx, 2, 0);		/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK111C? */
	xf_emit(ctx, 1, 0);		/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 000000ff UNK15F4_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK15F4_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 000000ff UNK0F84_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff UNK0F84_ADDRESS_LOW */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 00003fff VERTEX_ARRAY_ATTRIB_OFFSET */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 00000fff VERTEX_ARRAY_STRIDE */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VERTEX_ARRAY_LOW */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 000000ff VERTEX_ARRAY_HIGH */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* ffffffff VERTEX_LIMIT_LOW */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	xf_emit(ctx, acnt, 0);		/* 000000ff VERTEX_LIMIT_HIGH */
	xf_emit(ctx, 3, 0);		/* f/1f */
	/* SEEK */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, acnt, 0);		/* f */
		xf_emit(ctx, 3, 0);		/* f/1f */
	}
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 2, 0);	/* RO */
	else
		xf_emit(ctx, 5, 0);	/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffff DMA_VTXBUF */
	/* SEEK */
	if (device->chipset < 0xa0) {
		xf_emit(ctx, 0x41, 0);	/* RO */
		/* SEEK */
		xf_emit(ctx, 0x11, 0);	/* RO */
	} else if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x50, 0);	/* RO */
	else
		xf_emit(ctx, 0x58, 0);	/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, 1, 1);		/* 1 UNK0DEC */
	/* SEEK */
	xf_emit(ctx, acnt*4, 0);	/* ffffffff VTX_ATTR */
	xf_emit(ctx, 4, 0);		/* f/1f, 0, 0, 0 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x1d, 0);	/* RO */
	else
		xf_emit(ctx, 0x16, 0);	/* RO */
	/* SEEK */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTR_EN */
	/* SEEK */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 8, 0);	/* RO */
	else if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0xc, 0);	/* RO */
	else
		xf_emit(ctx, 7, 0);	/* RO */
	/* SEEK */
	xf_emit(ctx, 0xa, 0);		/* RO */
	if (device->chipset == 0xa0)
		rep = 0xc;
	else
		rep = 4;
	for (i = 0; i < rep; i++) {
		/* SEEK */
		if (IS_NVA3F(device->chipset))
			xf_emit(ctx, 0x20, 0);	/* ffffffff */
		xf_emit(ctx, 0x200, 0);	/* ffffffff */
		xf_emit(ctx, 4, 0);	/* 7f/ff, 0, 0, 0 */
		xf_emit(ctx, 4, 0);	/* ffffffff */
	}
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* 113/111 */
	xf_emit(ctx, 1, 0xf);		/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, (acnt/8)-1, 0);	/* ffffffff VP_ATTR_EN */
	xf_emit(ctx, acnt/8, 0);	/* ffffffff VTX_ATTR_MASK_UNK0DD0 */
	xf_emit(ctx, 1, 0);		/* 0000000f VP_GP_BUILTIN_ATTR_EN */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	/* SEEK */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 7, 0);	/* weird... */
	else
		xf_emit(ctx, 5, 0);	/* weird... */
}