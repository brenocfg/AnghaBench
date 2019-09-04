#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_2__ engine; } ;
struct TYPE_7__ {int x1; int y1; } ;
struct drm_plane_state {int src_w; int crtc_w; int src_h; int crtc_h; TYPE_3__ dst; TYPE_3__ src; TYPE_1__* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_format_info {int hsub; int vsub; } ;
struct TYPE_5__ {struct drm_format_info* format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_COORD (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_INSIZE (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_LAYER_SIZE (int,int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_OVL_SIZE (int) ; 
 int SUN8I_MIXER_COORD (int,int) ; 
 int SUN8I_MIXER_SIZE (int,int) ; 
 int drm_rect_height (TYPE_3__*) ; 
 int drm_rect_width (TYPE_3__*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun8i_vi_scaler_enable (struct sun8i_mixer*,int,int) ; 
 int /*<<< orphan*/  sun8i_vi_scaler_setup (struct sun8i_mixer*,int,int,int,int,int,int,int,int,int,struct drm_format_info const*) ; 

__attribute__((used)) static int sun8i_vi_layer_update_coord(struct sun8i_mixer *mixer, int channel,
				       int overlay, struct drm_plane *plane,
				       unsigned int zpos)
{
	struct drm_plane_state *state = plane->state;
	const struct drm_format_info *format = state->fb->format;
	u32 src_w, src_h, dst_w, dst_h;
	u32 outsize, insize;
	u32 hphase, vphase;
	bool subsampled;

	DRM_DEBUG_DRIVER("Updating VI channel %d overlay %d\n",
			 channel, overlay);

	src_w = drm_rect_width(&state->src) >> 16;
	src_h = drm_rect_height(&state->src) >> 16;
	dst_w = drm_rect_width(&state->dst);
	dst_h = drm_rect_height(&state->dst);

	hphase = state->src.x1 & 0xffff;
	vphase = state->src.y1 & 0xffff;

	/* make coordinates dividable by subsampling factor */
	if (format->hsub > 1) {
		int mask, remainder;

		mask = format->hsub - 1;
		remainder = (state->src.x1 >> 16) & mask;
		src_w = (src_w + remainder) & ~mask;
		hphase += remainder << 16;
	}

	if (format->vsub > 1) {
		int mask, remainder;

		mask = format->vsub - 1;
		remainder = (state->src.y1 >> 16) & mask;
		src_h = (src_h + remainder) & ~mask;
		vphase += remainder << 16;
	}

	insize = SUN8I_MIXER_SIZE(src_w, src_h);
	outsize = SUN8I_MIXER_SIZE(dst_w, dst_h);

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer source offset X: %d Y: %d\n",
			 (state->src.x1 >> 16) & ~(format->hsub - 1),
			 (state->src.y1 >> 16) & ~(format->vsub - 1));
	DRM_DEBUG_DRIVER("Layer source size W: %d H: %d\n", src_w, src_h);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_LAYER_SIZE(channel, overlay),
		     insize);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_OVL_SIZE(channel),
		     insize);

	/*
	 * Scaler must be enabled for subsampled formats, so it scales
	 * chroma to same size as luma.
	 */
	subsampled = format->hsub > 1 || format->vsub > 1;

	if (insize != outsize || subsampled || hphase || vphase) {
		u32 hscale, vscale;

		DRM_DEBUG_DRIVER("HW scaling is enabled\n");

		hscale = state->src_w / state->crtc_w;
		vscale = state->src_h / state->crtc_h;

		sun8i_vi_scaler_setup(mixer, channel, src_w, src_h, dst_w,
				      dst_h, hscale, vscale, hphase, vphase,
				      format);
		sun8i_vi_scaler_enable(mixer, channel, true);
	} else {
		DRM_DEBUG_DRIVER("HW scaling is not needed\n");
		sun8i_vi_scaler_enable(mixer, channel, false);
	}

	/* Set base coordinates */
	DRM_DEBUG_DRIVER("Layer destination coordinates X: %d Y: %d\n",
			 state->dst.x1, state->dst.y1);
	DRM_DEBUG_DRIVER("Layer destination size W: %d H: %d\n", dst_w, dst_h);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_COORD(zpos),
		     SUN8I_MIXER_COORD(state->dst.x1, state->dst.y1));
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_INSIZE(zpos),
		     outsize);

	return 0;
}