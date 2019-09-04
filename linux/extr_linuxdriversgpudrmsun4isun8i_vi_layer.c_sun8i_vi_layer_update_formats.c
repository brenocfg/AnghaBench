#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct sun8i_mixer {TYPE_3__ engine; } ;
struct drm_plane_state {TYPE_2__* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct de2_fmt_info {int de2_fmt; scalar_t__ csc; scalar_t__ rgb; } ;
struct TYPE_5__ {TYPE_1__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int EINVAL ; 
 scalar_t__ SUN8I_CSC_MODE_OFF ; 
 int /*<<< orphan*/  SUN8I_MIXER_CHAN_VI_LAYER_ATTR (int,int) ; 
 int SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_MASK ; 
 int SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_OFFSET ; 
 int SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sun8i_csc_enable_ccsc (struct sun8i_mixer*,int,int) ; 
 int /*<<< orphan*/  sun8i_csc_set_ccsc_coefficients (struct sun8i_mixer*,int,scalar_t__) ; 
 struct de2_fmt_info* sun8i_mixer_format_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_vi_layer_update_formats(struct sun8i_mixer *mixer, int channel,
					 int overlay, struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;
	const struct de2_fmt_info *fmt_info;
	u32 val;

	fmt_info = sun8i_mixer_format_info(state->fb->format->format);
	if (!fmt_info) {
		DRM_DEBUG_DRIVER("Invalid format\n");
		return -EINVAL;
	}

	val = fmt_info->de2_fmt << SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_OFFSET;
	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(channel, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_MASK, val);

	if (fmt_info->csc != SUN8I_CSC_MODE_OFF) {
		sun8i_csc_set_ccsc_coefficients(mixer, channel, fmt_info->csc);
		sun8i_csc_enable_ccsc(mixer, channel, true);
	} else {
		sun8i_csc_enable_ccsc(mixer, channel, false);
	}

	if (fmt_info->rgb)
		val = SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE;
	else
		val = 0;

	regmap_update_bits(mixer->engine.regs,
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR(channel, overlay),
			   SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE, val);

	return 0;
}