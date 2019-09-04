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
nv50_gr_construct_gene_ccache(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* RO */
	xf_emit(ctx, 0x800, 0);		/* ffffffff */
	switch (device->chipset) {
	case 0x50:
	case 0x92:
	case 0xa0:
		xf_emit(ctx, 0x2b, 0);
		break;
	case 0x84:
		xf_emit(ctx, 0x29, 0);
		break;
	case 0x94:
	case 0x96:
	case 0xa3:
		xf_emit(ctx, 0x27, 0);
		break;
	case 0x86:
	case 0x98:
	case 0xa5:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		xf_emit(ctx, 0x25, 0);
		break;
	}
	/* CB bindings, 0x80 of them. first word is address >> 8, second is
	 * size >> 4 | valid << 24 */
	xf_emit(ctx, 0x100, 0);		/* ffffffff CB_DEF */
	xf_emit(ctx, 1, 0);		/* 0000007f CB_ADDR_BUFFER */
	xf_emit(ctx, 1, 0);		/* 0 */
	xf_emit(ctx, 0x30, 0);		/* ff SET_PROGRAM_CB */
	xf_emit(ctx, 1, 0);		/* 3f last SET_PROGRAM_CB */
	xf_emit(ctx, 4, 0);		/* RO */
	xf_emit(ctx, 0x100, 0);		/* ffffffff */
	xf_emit(ctx, 8, 0);		/* 1f, 0, 0, ... */
	xf_emit(ctx, 8, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 3 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_CODE_CB */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TIC */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TSC */
	xf_emit(ctx, 1, 0);		/* 00000001 LINKED_TSC */
	xf_emit(ctx, 1, 0);		/* 000000ff TIC_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff TIC_ADDRESS_LOW */
	xf_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_LIMIT */
	xf_emit(ctx, 1, 0);		/* 000000ff TSC_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff TSC_ADDRESS_LOW */
	xf_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_LIMIT */
	xf_emit(ctx, 1, 0);		/* 000000ff VP_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff VP_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff VP_START_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff CB_DEF_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff CB_DEF_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0);		/* 000000ff GP_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff GP_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff GP_START_ID */
	xf_emit(ctx, 1, 0);		/* 000000ff FP_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff FP_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 00ffffff FP_START_ID */
}