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
typedef  int u32 ;
struct fimd_context {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLENDCON ; 
 int BLENDCON_NEW_8BIT_ALPHA_VALUE ; 
 int /*<<< orphan*/  BLENDCON_NEW_MASK ; 
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int VIDISD14C_ALPHA0_B (int) ; 
 int VIDISD14C_ALPHA0_G (int) ; 
 int VIDISD14C_ALPHA0_R (int) ; 
 int VIDISD14C_ALPHA1_B (int) ; 
 int VIDISD14C_ALPHA1_G (int) ; 
 int VIDISD14C_ALPHA1_R (int) ; 
 scalar_t__ VIDOSD_C (unsigned int) ; 
 int VIDW_ALPHA_B (int) ; 
 int VIDW_ALPHA_G (int) ; 
 int VIDW_ALPHA_R (int) ; 
 scalar_t__ VIDWnALPHA0 (unsigned int) ; 
 scalar_t__ VIDWnALPHA1 (unsigned int) ; 
 int /*<<< orphan*/  WINCON (unsigned int) ; 
 int WINCON1_ALPHA_MUL ; 
 int WINCON1_ALPHA_SEL ; 
 int WINCON1_BLD_PIX ; 
 int /*<<< orphan*/  WINCONx_BLEND_MODE_MASK ; 
 int /*<<< orphan*/  fimd_set_bits (struct fimd_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fimd_win_set_bldmod(struct fimd_context *ctx, unsigned int win,
				unsigned int alpha, unsigned int pixel_alpha)
{
	u32 win_alpha_l = (alpha >> 8) & 0xf;
	u32 win_alpha_h = alpha >> 12;
	u32 val = 0;

	switch (pixel_alpha) {
	case DRM_MODE_BLEND_PIXEL_NONE:
		break;
	case DRM_MODE_BLEND_COVERAGE:
	case DRM_MODE_BLEND_PREMULTI:
	default:
		val |= WINCON1_ALPHA_SEL;
		val |= WINCON1_BLD_PIX;
		val |= WINCON1_ALPHA_MUL;
		break;
	}
	fimd_set_bits(ctx, WINCON(win), WINCONx_BLEND_MODE_MASK, val);

	/* OSD alpha */
	val = VIDISD14C_ALPHA0_R(win_alpha_h) |
		VIDISD14C_ALPHA0_G(win_alpha_h) |
		VIDISD14C_ALPHA0_B(win_alpha_h) |
		VIDISD14C_ALPHA1_R(0x0) |
		VIDISD14C_ALPHA1_G(0x0) |
		VIDISD14C_ALPHA1_B(0x0);
	writel(val, ctx->regs + VIDOSD_C(win));

	val = VIDW_ALPHA_R(win_alpha_l) | VIDW_ALPHA_G(win_alpha_l) |
		VIDW_ALPHA_B(win_alpha_l);
	writel(val, ctx->regs + VIDWnALPHA0(win));

	val = VIDW_ALPHA_R(0x0) | VIDW_ALPHA_G(0x0) |
		VIDW_ALPHA_B(0x0);
	writel(val, ctx->regs + VIDWnALPHA1(win));

	fimd_set_bits(ctx, BLENDCON, BLENDCON_NEW_MASK,
			BLENDCON_NEW_8BIT_ALPHA_VALUE);
}