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
struct decon_context {int dummy; } ;

/* Variables and functions */
 int BLEND_NEW ; 
 int /*<<< orphan*/  DECON_BLENDCON ; 
 int /*<<< orphan*/  DECON_VIDOSDxC (unsigned int) ; 
 int /*<<< orphan*/  DECON_WINCONx (unsigned int) ; 
 unsigned int DRM_BLEND_ALPHA_OPAQUE ; 
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int VIDOSD_Wx_ALPHA_B_F (int) ; 
 int VIDOSD_Wx_ALPHA_G_F (int) ; 
 int VIDOSD_Wx_ALPHA_R_F (int) ; 
 int VIDOSDxC_ALPHA0_RGB_MASK ; 
 int WINCONx_ALPHA_MUL_F ; 
 int WINCONx_ALPHA_SEL_F ; 
 int WINCONx_BLD_PIX_F ; 
 int WINCONx_BLEND_MODE_MASK ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void decon_win_set_bldmod(struct decon_context *ctx, unsigned int win,
				 unsigned int alpha, unsigned int pixel_alpha)
{
	u32 win_alpha = alpha >> 8;
	u32 val = 0;

	switch (pixel_alpha) {
	case DRM_MODE_BLEND_PIXEL_NONE:
		break;
	case DRM_MODE_BLEND_COVERAGE:
	case DRM_MODE_BLEND_PREMULTI:
	default:
		val |= WINCONx_ALPHA_SEL_F;
		val |= WINCONx_BLD_PIX_F;
		val |= WINCONx_ALPHA_MUL_F;
		break;
	}
	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_BLEND_MODE_MASK, val);

	if (alpha != DRM_BLEND_ALPHA_OPAQUE) {
		val = VIDOSD_Wx_ALPHA_R_F(win_alpha) |
		      VIDOSD_Wx_ALPHA_G_F(win_alpha) |
		      VIDOSD_Wx_ALPHA_B_F(win_alpha);
		decon_set_bits(ctx, DECON_VIDOSDxC(win),
			       VIDOSDxC_ALPHA0_RGB_MASK, val);
		decon_set_bits(ctx, DECON_BLENDCON, BLEND_NEW, BLEND_NEW);
	}
}