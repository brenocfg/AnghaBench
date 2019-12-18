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
typedef  unsigned int u32 ;
struct mixer_context {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_BLEND_ALPHA_OPAQUE ; 
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int /*<<< orphan*/  MXR_GRAPHIC_CFG (unsigned int) ; 
 unsigned int MXR_GRP_CFG_BLEND_PRE_MUL ; 
 unsigned int MXR_GRP_CFG_COLOR_KEY_DISABLE ; 
 int /*<<< orphan*/  MXR_GRP_CFG_MISC_MASK ; 
 unsigned int MXR_GRP_CFG_PIXEL_BLEND_EN ; 
 unsigned int MXR_GRP_CFG_WIN_BLEND_EN ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_cfg_gfx_blend(struct mixer_context *ctx, unsigned int win,
				unsigned int pixel_alpha, unsigned int alpha)
{
	u32 win_alpha = alpha >> 8;
	u32 val;

	val  = MXR_GRP_CFG_COLOR_KEY_DISABLE; /* no blank key */
	switch (pixel_alpha) {
	case DRM_MODE_BLEND_PIXEL_NONE:
		break;
	case DRM_MODE_BLEND_COVERAGE:
		val |= MXR_GRP_CFG_PIXEL_BLEND_EN;
		break;
	case DRM_MODE_BLEND_PREMULTI:
	default:
		val |= MXR_GRP_CFG_BLEND_PRE_MUL;
		val |= MXR_GRP_CFG_PIXEL_BLEND_EN;
		break;
	}

	if (alpha != DRM_BLEND_ALPHA_OPAQUE) {
		val |= MXR_GRP_CFG_WIN_BLEND_EN;
		val |= win_alpha;
	}
	mixer_reg_writemask(ctx, MXR_GRAPHIC_CFG(win),
			    val, MXR_GRP_CFG_MISC_MASK);
}