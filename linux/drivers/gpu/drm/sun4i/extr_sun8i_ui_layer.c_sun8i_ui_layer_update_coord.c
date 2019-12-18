#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_10__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_4__ engine; } ;
struct TYPE_11__ {int x1; int y1; } ;
struct drm_plane_state {scalar_t__ src_w; scalar_t__ crtc_w; scalar_t__ src_h; scalar_t__ crtc_h; TYPE_5__ dst; TYPE_5__ src; TYPE_3__* crtc; } ;
struct drm_plane {scalar_t__ type; struct drm_plane_state* state; } ;
struct TYPE_9__ {TYPE_2__* state; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_1__ adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_COORD (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_ATTR_INSIZE (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_OUTCTL (scalar_t__) ; 
 scalar_t__ SUN8I_MIXER_BLEND_OUTCTL_INTERLACED ; 
 int /*<<< orphan*/  SUN8I_MIXER_BLEND_OUTSIZE (scalar_t__) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_UI_LAYER_SIZE (scalar_t__,int) ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_UI_OVL_SIZE (scalar_t__) ; 
 scalar_t__ SUN8I_MIXER_COORD (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SUN8I_MIXER_GLOBAL_SIZE ; 
 scalar_t__ SUN8I_MIXER_SIZE (scalar_t__,scalar_t__) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sun8i_blender_base (struct sun8i_mixer*) ; 
 scalar_t__ sun8i_channel_base (struct sun8i_mixer*,int) ; 
 int /*<<< orphan*/  sun8i_ui_scaler_enable (struct sun8i_mixer*,int,int) ; 
 int /*<<< orphan*/  sun8i_ui_scaler_setup (struct sun8i_mixer*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sun8i_ui_layer_update_coord(struct sun8i_mixer *mixer, int channel,
				       int overlay, struct drm_plane *plane,
				       unsigned int zpos)
{
	struct drm_plane_state *state = plane->state;
	u32 src_w, src_h, dst_w, dst_h;
	u32 bld_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;

	DRM_DEBUG_DRIVER("Updating UI channel %d overlay %d\n",
			 channel, overlay);

	bld_base = sun8i_blender_base(mixer);
	ch_base = sun8i_channel_base(mixer, channel);

	src_w = drm_rect_width(&state->src) >> 16;
	src_h = drm_rect_height(&state->src) >> 16;
	dst_w = drm_rect_width(&state->dst);
	dst_h = drm_rect_height(&state->dst);

	hphase = state->src.x1 & 0xffff;
	vphase = state->src.y1 & 0xffff;

	insize = SUN8I_MIXER_SIZE(src_w, src_h);
	outsize = SUN8I_MIXER_SIZE(dst_w, dst_h);

	if (plane->type == DRM_PLANE_TYPE_PRIMARY) {
		bool interlaced = false;
		u32 val;

		DRM_DEBUG_DRIVER("Primary layer, updating global size W: %u H: %u\n",
				 dst_w, dst_h);
		regmap_write(mixer->engine.regs,
			     SUN8I_MIXER_GLOBAL_SIZE,
			     outsize);
		regmap_write(mixer->engine.regs,
			     SUN8I_MIXER_BLEND_OUTSIZE(bld_base), outsize);

		if (state->crtc)
			interlaced = state->crtc->state->adjusted_mode.flags
				& DRM_MODE_FLAG_INTERLACE;

		if (interlaced)
			val = SUN8I_MIXER_BLEND_OUTCTL_INTERLACED;
		else
			val = 0;

		regmap_update_bits(mixer->engine.regs,
				   SUN8I_MIXER_BLEND_OUTCTL(bld_base),
				   SUN8I_MIXER_BLEND_OUTCTL_INTERLACED,
				   val);

		DRM_DEBUG_DRIVER("Switching display mixer interlaced mode %s\n",
				 interlaced ? "on" : "off");
	}

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer source offset X: %d Y: %d\n",
			 state->src.x1 >> 16, state->src.y1 >> 16);
	DRM_DEBUG_DRIVER("Layer source size W: %d H: %d\n", src_w, src_h);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_LAYER_SIZE(ch_base, overlay),
		     insize);
	regmap_write(mixer->engine.regs,
		     SUN8I_MIXER_CHAN_UI_OVL_SIZE(ch_base),
		     insize);

	if (insize != outsize || hphase || vphase) {
		u32 hscale, vscale;

		DRM_DEBUG_DRIVER("HW scaling is enabled\n");

		hscale = state->src_w / state->crtc_w;
		vscale = state->src_h / state->crtc_h;

		sun8i_ui_scaler_setup(mixer, channel, src_w, src_h, dst_w,
				      dst_h, hscale, vscale, hphase, vphase);
		sun8i_ui_scaler_enable(mixer, channel, true);
	} else {
		DRM_DEBUG_DRIVER("HW scaling is not needed\n");
		sun8i_ui_scaler_enable(mixer, channel, false);
	}

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