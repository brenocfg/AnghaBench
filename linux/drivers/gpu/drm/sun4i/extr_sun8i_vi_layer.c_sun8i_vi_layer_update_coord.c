#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_5__ engine; TYPE_4__* cfg; int /*<<< orphan*/  mod_clk; } ;
struct TYPE_13__ {int x1; int y1; } ;
struct drm_plane_state {TYPE_6__ dst; TYPE_3__* crtc; TYPE_6__ src; TYPE_1__* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_format_info {int hsub; int vsub; } ;
struct drm_display_mode {int clock; int vtotal; int htotal; int vdisplay; } ;
struct TYPE_11__ {int scanline_yuv; } ;
struct TYPE_10__ {TYPE_2__* state; } ;
struct TYPE_9__ {struct drm_display_mode mode; } ;
struct TYPE_8__ {struct drm_format_info* format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_COORD (int,unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_INSIZE (int,unsigned int) ; 
 int SUN8I_MIXER_CHAN_VI_DS_M (int) ; 
 int SUN8I_MIXER_CHAN_VI_DS_N (int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_HDS_UV (int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_HDS_Y (int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_LAYER_SIZE (int,int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_OVL_SIZE (int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_VDS_UV (int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_VDS_Y (int) ; 
 int SUN8I_MIXER_COORD (int,int) ; 
 int SUN8I_MIXER_SIZE (int,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int drm_rect_height (TYPE_6__*) ; 
 int drm_rect_width (TYPE_6__*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sun8i_blender_base (struct sun8i_mixer*) ; 
 int sun8i_channel_base (struct sun8i_mixer*,int) ; 
 int /*<<< orphan*/  sun8i_vi_scaler_enable (struct sun8i_mixer*,int,int) ; 
 int /*<<< orphan*/  sun8i_vi_scaler_setup (struct sun8i_mixer*,int,int,int,int,int,int,int,int,int,struct drm_format_info const*) ; 

__attribute__((used)) static int sun8i_vi_layer_update_coord(struct sun8i_mixer *mixer, int channel,
				       int overlay, struct drm_plane *plane,
				       unsigned int zpos)
{
	struct drm_plane_state *state = plane->state;
	const struct drm_format_info *format = state->fb->format;
	u32 src_w, src_h, dst_w, dst_h;
	u32 bld_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;
	u32 hn = 0, hm = 0;
	u32 vn = 0, vm = 0;
	bool subsampled;

	DRM_DEBUG_DRIVER("Updating VI channel %d overlay %d\n",
			 channel, overlay);

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

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
		     SUN8I_MIXER_CHAN_VI_LAYER_SIZE(ch_base, overlay),
		     insize);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_OVL_SIZE(ch_base),
		     insize);

	/*
	 * Scaler must be enabled for subsampled formats, so it scales
	 * chroma to same size as luma.
	 */
	subsampled = format->hsub > 1 || format->vsub > 1;

	if (insize != outsize || subsampled || hphase || vphase) {
		unsigned int scanline, required;
		struct drm_display_mode *mode;
		u32 hscale, vscale, fps;
		u64 ability;

		DRM_DEBUG_DRIVER("HW scaling is enabled\n");

		mode = &plane->state->crtc->state->mode;
		fps = (mode->clock * 1000) / (mode->vtotal * mode->htotal);
		ability = clk_get_rate(mixer->mod_clk);
		/* BSP algorithm assumes 80% efficiency of VI scaler unit */
		ability *= 80;
		do_div(ability, mode->vdisplay * fps * max(src_w, dst_w));

		required = src_h * 100 / dst_h;

		if (ability < required) {
			DRM_DEBUG_DRIVER("Using vertical coarse scaling\n");
			vm = src_h;
			vn = (u32)ability * dst_h / 100;
			src_h = vn;
		}

		/* it seems that every RGB scaler has buffer for 2048 pixels */
		scanline = subsampled ? mixer->cfg->scanline_yuv : 2048;

		if (src_w > scanline) {
			DRM_DEBUG_DRIVER("Using horizontal coarse scaling\n");
			hm = src_w;
			hn = scanline;
			src_w = hn;
		}

		hscale = (src_w << 16) / dst_w;
		vscale = (src_h << 16) / dst_h;

		sun8i_vi_scaler_setup(mixer, channel, src_w, src_h, dst_w,
				      dst_h, hscale, vscale, hphase, vphase,
				      format);
		sun8i_vi_scaler_enable(mixer, channel, true);
	} else {
		DRM_DEBUG_DRIVER("HW scaling is not needed\n");
		sun8i_vi_scaler_enable(mixer, channel, false);
	}

	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_HDS_Y(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(hm));
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_HDS_UV(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(hm));
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_VDS_Y(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(vm));
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_VI_VDS_UV(ch_base),
		     SUN8I_MIXER_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXER_CHAN_VI_DS_M(vm));

	/* Set base coordinates */
	DRM_DEBUG_DRIVER("Layer destination coordinates X: %d Y: %d\n",
			 state->dst.x1, state->dst.y1);
	DRM_DEBUG_DRIVER("Layer destination size W: %d H: %d\n", dst_w, dst_h);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_COORD(bld_base, zpos),
		     SUN8I_MIXER_COORD(state->dst.x1, state->dst.y1));
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_BLEND_ATTR_INSIZE(bld_base, zpos),
		     outsize);

	return 0;
}