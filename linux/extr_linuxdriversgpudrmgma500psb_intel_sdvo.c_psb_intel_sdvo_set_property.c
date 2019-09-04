#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  void* uint16_t ;
struct psb_intel_sdvo_connector {int force_audio; scalar_t__* tv_format_supported; void* left_margin; void* right_margin; void* max_hscan; void* top_margin; void* bottom_margin; void* max_vscan; void* cur_hpos; void* max_hpos; void* cur_vpos; void* max_vpos; void* cur_saturation; void* max_saturation; void* cur_contrast; void* max_contrast; void* cur_hue; void* max_hue; void* cur_brightness; void* max_brightness; void* cur_sharpness; void* max_sharpness; void* cur_flicker_filter; void* max_flicker_filter; void* cur_flicker_filter_2d; void* max_flicker_filter_2d; void* cur_flicker_filter_adaptive; void* max_flicker_filter_adaptive; void* cur_tv_chroma_filter; void* max_tv_chroma_filter; void* cur_tv_luma_filter; void* max_tv_luma_filter; void* cur_dot_crawl; void* max_dot_crawl; struct drm_property* dot_crawl; struct drm_property* tv_luma_filter; struct drm_property* tv_chroma_filter; struct drm_property* flicker_filter_adaptive; struct drm_property* flicker_filter_2d; struct drm_property* flicker_filter; struct drm_property* sharpness; struct drm_property* brightness; struct drm_property* hue; struct drm_property* contrast; struct drm_property* saturation; struct drm_property* vpos; struct drm_property* hpos; struct drm_property* top; struct drm_property* bottom; struct drm_property* left; struct drm_property* right; struct drm_property* tv_format; } ;
struct TYPE_5__ {struct drm_crtc* crtc; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct psb_intel_sdvo {int has_hdmi_audio; scalar_t__ tv_format_index; TYPE_2__ base; int /*<<< orphan*/  color_range; } ;
struct drm_psb_private {struct drm_property* broadcast_rgb_property; struct drm_property* force_audio_property; } ;
struct drm_property {int dummy; } ;
struct drm_crtc {TYPE_3__* primary; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  mode; } ;
struct drm_connector {int /*<<< orphan*/  base; TYPE_4__* dev; } ;
struct TYPE_8__ {struct drm_psb_private* dev_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IS_TV_OR_LVDS (struct psb_intel_sdvo_connector*) ; 
 int /*<<< orphan*/  SDVO_CMD_SET_BRIGHTNESS ; 
 int /*<<< orphan*/  SDVO_CMD_SET_CONTRAST ; 
 int /*<<< orphan*/  SDVO_CMD_SET_DOT_CRAWL ; 
 int /*<<< orphan*/  SDVO_CMD_SET_FLICKER_FILTER ; 
 int /*<<< orphan*/  SDVO_CMD_SET_FLICKER_FILTER_2D ; 
 int /*<<< orphan*/  SDVO_CMD_SET_FLICKER_FILTER_ADAPTIVE ; 
 int /*<<< orphan*/  SDVO_CMD_SET_HPOS ; 
 int /*<<< orphan*/  SDVO_CMD_SET_HUE ; 
 int /*<<< orphan*/  SDVO_CMD_SET_OVERSCAN_H ; 
 int /*<<< orphan*/  SDVO_CMD_SET_OVERSCAN_V ; 
 int /*<<< orphan*/  SDVO_CMD_SET_SATURATION ; 
 int /*<<< orphan*/  SDVO_CMD_SET_SHARPNESS ; 
 int /*<<< orphan*/  SDVO_CMD_SET_TV_CHROMA_FILTER ; 
 int /*<<< orphan*/  SDVO_CMD_SET_TV_LUMA_FILTER ; 
 int /*<<< orphan*/  SDVO_CMD_SET_VPOS ; 
 int /*<<< orphan*/  SDVO_COLOR_RANGE_16_235 ; 
 int /*<<< orphan*/  drm_crtc_helper_set_mode (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_object_property_set_value (int /*<<< orphan*/ *,struct drm_property*,int) ; 
 struct psb_intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 int psb_intel_sdvo_detect_hdmi_audio (struct drm_connector*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,void**,int) ; 
 struct psb_intel_sdvo_connector* to_psb_intel_sdvo_connector (struct drm_connector*) ; 
 int /*<<< orphan*/  tv_format_names ; 

__attribute__((used)) static int
psb_intel_sdvo_set_property(struct drm_connector *connector,
			struct drm_property *property,
			uint64_t val)
{
	struct psb_intel_sdvo *psb_intel_sdvo = intel_attached_sdvo(connector);
	struct psb_intel_sdvo_connector *psb_intel_sdvo_connector = to_psb_intel_sdvo_connector(connector);
	struct drm_psb_private *dev_priv = connector->dev->dev_private;
	uint16_t temp_value;
	uint8_t cmd;
	int ret;

	ret = drm_object_property_set_value(&connector->base, property, val);
	if (ret)
		return ret;

	if (property == dev_priv->force_audio_property) {
		int i = val;
		bool has_audio;

		if (i == psb_intel_sdvo_connector->force_audio)
			return 0;

		psb_intel_sdvo_connector->force_audio = i;

		if (i == 0)
			has_audio = psb_intel_sdvo_detect_hdmi_audio(connector);
		else
			has_audio = i > 0;

		if (has_audio == psb_intel_sdvo->has_hdmi_audio)
			return 0;

		psb_intel_sdvo->has_hdmi_audio = has_audio;
		goto done;
	}

	if (property == dev_priv->broadcast_rgb_property) {
		if (val == !!psb_intel_sdvo->color_range)
			return 0;

		psb_intel_sdvo->color_range = val ? SDVO_COLOR_RANGE_16_235 : 0;
		goto done;
	}

#define CHECK_PROPERTY(name, NAME) \
	if (psb_intel_sdvo_connector->name == property) { \
		if (psb_intel_sdvo_connector->cur_##name == temp_value) return 0; \
		if (psb_intel_sdvo_connector->max_##name < temp_value) return -EINVAL; \
		cmd = SDVO_CMD_SET_##NAME; \
		psb_intel_sdvo_connector->cur_##name = temp_value; \
		goto set_value; \
	}

	if (property == psb_intel_sdvo_connector->tv_format) {
		if (val >= ARRAY_SIZE(tv_format_names))
			return -EINVAL;

		if (psb_intel_sdvo->tv_format_index ==
		    psb_intel_sdvo_connector->tv_format_supported[val])
			return 0;

		psb_intel_sdvo->tv_format_index = psb_intel_sdvo_connector->tv_format_supported[val];
		goto done;
	} else if (IS_TV_OR_LVDS(psb_intel_sdvo_connector)) {
		temp_value = val;
		if (psb_intel_sdvo_connector->left == property) {
			drm_object_property_set_value(&connector->base,
							 psb_intel_sdvo_connector->right, val);
			if (psb_intel_sdvo_connector->left_margin == temp_value)
				return 0;

			psb_intel_sdvo_connector->left_margin = temp_value;
			psb_intel_sdvo_connector->right_margin = temp_value;
			temp_value = psb_intel_sdvo_connector->max_hscan -
				psb_intel_sdvo_connector->left_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_H;
			goto set_value;
		} else if (psb_intel_sdvo_connector->right == property) {
			drm_object_property_set_value(&connector->base,
							 psb_intel_sdvo_connector->left, val);
			if (psb_intel_sdvo_connector->right_margin == temp_value)
				return 0;

			psb_intel_sdvo_connector->left_margin = temp_value;
			psb_intel_sdvo_connector->right_margin = temp_value;
			temp_value = psb_intel_sdvo_connector->max_hscan -
				psb_intel_sdvo_connector->left_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_H;
			goto set_value;
		} else if (psb_intel_sdvo_connector->top == property) {
			drm_object_property_set_value(&connector->base,
							 psb_intel_sdvo_connector->bottom, val);
			if (psb_intel_sdvo_connector->top_margin == temp_value)
				return 0;

			psb_intel_sdvo_connector->top_margin = temp_value;
			psb_intel_sdvo_connector->bottom_margin = temp_value;
			temp_value = psb_intel_sdvo_connector->max_vscan -
				psb_intel_sdvo_connector->top_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_V;
			goto set_value;
		} else if (psb_intel_sdvo_connector->bottom == property) {
			drm_object_property_set_value(&connector->base,
							 psb_intel_sdvo_connector->top, val);
			if (psb_intel_sdvo_connector->bottom_margin == temp_value)
				return 0;

			psb_intel_sdvo_connector->top_margin = temp_value;
			psb_intel_sdvo_connector->bottom_margin = temp_value;
			temp_value = psb_intel_sdvo_connector->max_vscan -
				psb_intel_sdvo_connector->top_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_V;
			goto set_value;
		}
		CHECK_PROPERTY(hpos, HPOS)
		CHECK_PROPERTY(vpos, VPOS)
		CHECK_PROPERTY(saturation, SATURATION)
		CHECK_PROPERTY(contrast, CONTRAST)
		CHECK_PROPERTY(hue, HUE)
		CHECK_PROPERTY(brightness, BRIGHTNESS)
		CHECK_PROPERTY(sharpness, SHARPNESS)
		CHECK_PROPERTY(flicker_filter, FLICKER_FILTER)
		CHECK_PROPERTY(flicker_filter_2d, FLICKER_FILTER_2D)
		CHECK_PROPERTY(flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE)
		CHECK_PROPERTY(tv_chroma_filter, TV_CHROMA_FILTER)
		CHECK_PROPERTY(tv_luma_filter, TV_LUMA_FILTER)
		CHECK_PROPERTY(dot_crawl, DOT_CRAWL)
	}

	return -EINVAL; /* unknown property */

set_value:
	if (!psb_intel_sdvo_set_value(psb_intel_sdvo, cmd, &temp_value, 2))
		return -EIO;


done:
	if (psb_intel_sdvo->base.base.crtc) {
		struct drm_crtc *crtc = psb_intel_sdvo->base.base.crtc;
		drm_crtc_helper_set_mode(crtc, &crtc->mode, crtc->x,
					 crtc->y, crtc->primary->fb);
	}

	return 0;
#undef CHECK_PROPERTY
}