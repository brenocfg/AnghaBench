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
nv50_gr_construct_xfer_tprop(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	int magic1, magic2;
	if (device->chipset == 0x50) {
		magic1 = 0x3ff;
		magic2 = 0x00003e60;
	} else if (!IS_NVA3F(device->chipset)) {
		magic1 = 0x7ff;
		magic2 = 0x001ffe67;
	} else {
		magic1 = 0x7ff;
		magic2 = 0x00087e67;
	}
	xf_emit(ctx, 1, 0);		/* 00000007 ALPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* ffffffff ALPHA_TEST_REF */
	xf_emit(ctx, 1, 0);		/* 00000001 ALPHA_TEST_ENABLE */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000000f UNK16A0 */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_BACK_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 4, 0);		/* ffffffff BLEND_COLOR */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK19C0 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK0FDC */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 LOGIC_OP_ENABLE */
	xf_emit(ctx, 1, 0);		/* ff[NV50]/3ff[NV84+] */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_FRONT_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK19CC */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff COLOR_KEY */
	xf_emit(ctx, 1, 0);		/* 00000001 COLOR_KEY_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 COLOR_KEY_FORMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff SIFC_BITMAP_COLOR */
	xf_emit(ctx, 1, 1);		/* 00000001 SIFC_BITMAP_WRITE_BIT0_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 ALPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 ALPHA_TEST_ENABLE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 3);	/* 00000003 tesla UNK16B4 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 00000003 tesla UNK1298 */
	} else if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 1);	/* 00000001 tesla UNK16B4 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
	} else {
		xf_emit(ctx, 1, 0);	/* 00000003 MULTISAMPLE_CTRL */
	}
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 8, 0);		/* 00000001 BLEND_ENABLE */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_ALPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_ALPHA */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_ALPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_RGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_RGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_RGB */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 UNK12E4 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_RGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_ALPHA */
		xf_emit(ctx, 8, 1);	/* 00000001 IBLEND_UNK00 */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_SRC_RGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_DST_RGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_SRC_ALPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_DST_ALPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
	}
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000001 LOGIC_OP_ENABLE */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 FRAMEBUFFER_SRGB */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	xf_emit(ctx, 1, 0);		/* 00000007 OPERATION */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SIFC_FORMAT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff DRAW_COLOR_FORMAT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SRC_FORMAT */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f[NVA3] MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 8, 0);		/* 00000001 BLEND_ENABLE */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_ALPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_ALPHA */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_ALPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_RGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_RGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_RGB */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 8, 1);		/* 00000001 UNK19E0 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, magic2);	/* 001fffff tesla UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0);	/* ff */
	else
		xf_emit(ctx, 3, 0);	/* 1, 7, 3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_DU_DX_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BLIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_DV_DY_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BLIT_DV_DY_INT */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, magic1);	/* 3ff/7ff tesla UNK0D68 */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	xf_emit(ctx, 8, 0);		/* 0000ffff DMA_COLOR */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_GLOBAL */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_LOCAL */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_STACK */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_DST */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 8, 0);		/* 000000ff RT_ADDRESS_HIGH */
	xf_emit(ctx, 8, 0);		/* ffffffff RT_LAYER_STRIDE */
	xf_emit(ctx, 8, 0);		/* ffffffff RT_ADDRESS_LOW */
	xf_emit(ctx, 8, 8);		/* 0000007f RT_TILE_MODE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 8, 0x400);		/* 0fffffff RT_HORIZ */
	xf_emit(ctx, 8, 0x300);		/* 0000ffff RT_VERT */
	xf_emit(ctx, 1, 1);		/* 00001fff RT_ARRAY_MODE */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, 0x20);		/* 00000fff DST_TILE_MODE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_HEIGHT */
	xf_emit(ctx, 1, 0);		/* 000007ff DST_LAYER */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	xf_emit(ctx, 1, 0);		/* ffffffff DST_ADDRESS_LOW */
	xf_emit(ctx, 1, 0);		/* 000000ff DST_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0x40);		/* 0007ffff DST_PITCH */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_WIDTH */
	xf_emit(ctx, 1, 0);		/* 0000ffff */
	xf_emit(ctx, 1, 3);		/* 00000003 tesla UNK15AC */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	xf_emit(ctx, 1, magic2);	/* 001fffff tesla UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 2);		/* 00000003 tesla UNK143C */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_ZETA */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 2, 0);		/* ffff, ff/3ff */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* ffffffff ZETA_LAYER_STRIDE */
	xf_emit(ctx, 1, 0);		/* 000000ff ZETA_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);		/* ffffffff ZETA_ADDRESS_LOW */
	xf_emit(ctx, 1, 4);		/* 00000007 ZETA_TILE_MODE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0x400);		/* 0fffffff ZETA_HORIZ */
	xf_emit(ctx, 1, 0x300);		/* 0000ffff ZETA_VERT */
	xf_emit(ctx, 1, 0x1001);	/* 00001fff ZETA_ARRAY_MODE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);	/* 00000001 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 8, 0);		/* 00000001 BLEND_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 1, 0);		/* 00000001 FRAMEBUFFER_SRGB */
	xf_emit(ctx, 1, 0);		/* 7 */
	xf_emit(ctx, 1, 0);		/* 00000001 LOGIC_OP_ENABLE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	}
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x0fac6881);	/* fffffff */
	xf_emit(ctx, 1, magic2);	/* 001fffff tesla UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK19CC */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
		xf_emit(ctx, 1, 0);	/* 0000000f tesla UNK15C8 */
	}
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 3, 0);		/* 7/f, 1, ffff0ff3 */
		xf_emit(ctx, 1, 0xfac6881);	/* fffffff */
		xf_emit(ctx, 4, 0);		/* 1, 1, 1, 3ff */
		xf_emit(ctx, 1, 4);		/* 7 */
		xf_emit(ctx, 1, 0);		/* 1 */
		xf_emit(ctx, 2, 1);		/* 1 */
		xf_emit(ctx, 2, 0);		/* 7, f */
		xf_emit(ctx, 1, 1);		/* 1 */
		xf_emit(ctx, 1, 0);		/* 7/f */
		if (IS_NVA3F(device->chipset))
			xf_emit(ctx, 0x9, 0);	/* 1 */
		else
			xf_emit(ctx, 0x8, 0);	/* 1 */
		xf_emit(ctx, 1, 0);		/* ffff0ff3 */
		xf_emit(ctx, 8, 1);		/* 1 */
		xf_emit(ctx, 1, 0x11);		/* 7f */
		xf_emit(ctx, 7, 0);		/* 7f */
		xf_emit(ctx, 1, 0xfac6881);	/* fffffff */
		xf_emit(ctx, 1, 0xf);		/* f */
		xf_emit(ctx, 7, 0);		/* f */
		xf_emit(ctx, 1, 0x11);		/* 7f */
		xf_emit(ctx, 1, 1);		/* 1 */
		xf_emit(ctx, 5, 0);		/* 1, 7, 3ff, 3, 7 */
		if (IS_NVA3F(device->chipset)) {
			xf_emit(ctx, 1, 0);	/* 00000001 UNK1140 */
			xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
		}
	}
}