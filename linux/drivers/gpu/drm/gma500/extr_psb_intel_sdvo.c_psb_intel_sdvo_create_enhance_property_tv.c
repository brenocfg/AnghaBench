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
typedef  int uint16_t ;
struct psb_intel_sdvo_enhancements_reply {scalar_t__ dot_crawl; scalar_t__ overscan_v; scalar_t__ overscan_h; } ;
struct drm_connector {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {struct drm_connector base; } ;
struct psb_intel_sdvo_connector {int max_hscan; int left_margin; int right_margin; int max_vscan; int top_margin; int bottom_margin; int max_dot_crawl; int cur_dot_crawl; void* dot_crawl; void* bottom; void* top; void* right; void* left; TYPE_3__ base; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct psb_intel_sdvo {TYPE_2__ base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIGHTNESS ; 
 int /*<<< orphan*/  CONTRAST ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  ENHANCEMENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLICKER_FILTER ; 
 int /*<<< orphan*/  FLICKER_FILTER_2D ; 
 int /*<<< orphan*/  FLICKER_FILTER_ADAPTIVE ; 
 int /*<<< orphan*/  HPOS ; 
 int /*<<< orphan*/  HUE ; 
 int /*<<< orphan*/  SATURATION ; 
 int /*<<< orphan*/  SDVO_CMD_GET_DOT_CRAWL ; 
 int /*<<< orphan*/  SDVO_CMD_GET_MAX_OVERSCAN_H ; 
 int /*<<< orphan*/  SDVO_CMD_GET_MAX_OVERSCAN_V ; 
 int /*<<< orphan*/  SDVO_CMD_GET_OVERSCAN_H ; 
 int /*<<< orphan*/  SDVO_CMD_GET_OVERSCAN_V ; 
 int /*<<< orphan*/  SHARPNESS ; 
 int /*<<< orphan*/  TV_CHROMA_FILTER ; 
 int /*<<< orphan*/  TV_LUMA_FILTER ; 
 int /*<<< orphan*/  VPOS ; 
 int /*<<< orphan*/  brightness ; 
 int /*<<< orphan*/  contrast ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,void*,int) ; 
 void* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flicker_filter ; 
 int /*<<< orphan*/  flicker_filter_2d ; 
 int /*<<< orphan*/  flicker_filter_adaptive ; 
 int /*<<< orphan*/  hpos ; 
 int /*<<< orphan*/  hue ; 
 int /*<<< orphan*/  psb_intel_sdvo_get_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  saturation ; 
 int /*<<< orphan*/  sharpness ; 
 int /*<<< orphan*/  tv_chroma_filter ; 
 int /*<<< orphan*/  tv_luma_filter ; 
 int /*<<< orphan*/  vpos ; 

__attribute__((used)) static bool
psb_intel_sdvo_create_enhance_property_tv(struct psb_intel_sdvo *psb_intel_sdvo,
				      struct psb_intel_sdvo_connector *psb_intel_sdvo_connector,
				      struct psb_intel_sdvo_enhancements_reply enhancements)
{
	struct drm_device *dev = psb_intel_sdvo->base.base.dev;
	struct drm_connector *connector = &psb_intel_sdvo_connector->base.base;
	uint16_t response, data_value[2];

	/* when horizontal overscan is supported, Add the left/right  property */
	if (enhancements.overscan_h) {
		if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_H,
					  &data_value, 4))
			return false;

		if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_H,
					  &response, 2))
			return false;

		psb_intel_sdvo_connector->max_hscan = data_value[0];
		psb_intel_sdvo_connector->left_margin = data_value[0] - response;
		psb_intel_sdvo_connector->right_margin = psb_intel_sdvo_connector->left_margin;
		psb_intel_sdvo_connector->left =
			drm_property_create_range(dev, 0, "left_margin", 0, data_value[0]);
		if (!psb_intel_sdvo_connector->left)
			return false;

		drm_object_attach_property(&connector->base,
					      psb_intel_sdvo_connector->left,
					      psb_intel_sdvo_connector->left_margin);

		psb_intel_sdvo_connector->right =
			drm_property_create_range(dev, 0, "right_margin", 0, data_value[0]);
		if (!psb_intel_sdvo_connector->right)
			return false;

		drm_object_attach_property(&connector->base,
					      psb_intel_sdvo_connector->right,
					      psb_intel_sdvo_connector->right_margin);
		DRM_DEBUG_KMS("h_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	}

	if (enhancements.overscan_v) {
		if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_V,
					  &data_value, 4))
			return false;

		if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_V,
					  &response, 2))
			return false;

		psb_intel_sdvo_connector->max_vscan = data_value[0];
		psb_intel_sdvo_connector->top_margin = data_value[0] - response;
		psb_intel_sdvo_connector->bottom_margin = psb_intel_sdvo_connector->top_margin;
		psb_intel_sdvo_connector->top =
			drm_property_create_range(dev, 0, "top_margin", 0, data_value[0]);
		if (!psb_intel_sdvo_connector->top)
			return false;

		drm_object_attach_property(&connector->base,
					      psb_intel_sdvo_connector->top,
					      psb_intel_sdvo_connector->top_margin);

		psb_intel_sdvo_connector->bottom =
			drm_property_create_range(dev, 0, "bottom_margin", 0, data_value[0]);
		if (!psb_intel_sdvo_connector->bottom)
			return false;

		drm_object_attach_property(&connector->base,
					      psb_intel_sdvo_connector->bottom,
					      psb_intel_sdvo_connector->bottom_margin);
		DRM_DEBUG_KMS("v_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	}

	ENHANCEMENT(hpos, HPOS);
	ENHANCEMENT(vpos, VPOS);
	ENHANCEMENT(saturation, SATURATION);
	ENHANCEMENT(contrast, CONTRAST);
	ENHANCEMENT(hue, HUE);
	ENHANCEMENT(sharpness, SHARPNESS);
	ENHANCEMENT(brightness, BRIGHTNESS);
	ENHANCEMENT(flicker_filter, FLICKER_FILTER);
	ENHANCEMENT(flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE);
	ENHANCEMENT(flicker_filter_2d, FLICKER_FILTER_2D);
	ENHANCEMENT(tv_chroma_filter, TV_CHROMA_FILTER);
	ENHANCEMENT(tv_luma_filter, TV_LUMA_FILTER);

	if (enhancements.dot_crawl) {
		if (!psb_intel_sdvo_get_value(psb_intel_sdvo, SDVO_CMD_GET_DOT_CRAWL, &response, 2))
			return false;

		psb_intel_sdvo_connector->max_dot_crawl = 1;
		psb_intel_sdvo_connector->cur_dot_crawl = response & 0x1;
		psb_intel_sdvo_connector->dot_crawl =
			drm_property_create_range(dev, 0, "dot_crawl", 0, 1);
		if (!psb_intel_sdvo_connector->dot_crawl)
			return false;

		drm_object_attach_property(&connector->base,
					      psb_intel_sdvo_connector->dot_crawl,
					      psb_intel_sdvo_connector->cur_dot_crawl);
		DRM_DEBUG_KMS("dot crawl: current %d\n", response);
	}

	return true;
}