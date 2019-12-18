#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_info {int interlaced; int v_sync_polarity; int h_sync_polarity; void* color_depth; void* ycbcr_coeff; void* dynamic_range; void* color_space; } ;
struct drm_display_mode {int flags; } ;
struct drm_display_info {int bpc; int color_formats; } ;
struct drm_bridge {struct analogix_dp_device* driver_private; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct drm_display_info display_info; } ;
struct analogix_dp_device {TYPE_2__* dev; struct video_info video_info; TYPE_1__ connector; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 void* CEA ; 
 void* COLOR_10 ; 
 void* COLOR_12 ; 
 void* COLOR_6 ; 
 void* COLOR_8 ; 
 void* COLOR_RGB ; 
 void* COLOR_YCBCR422 ; 
 void* COLOR_YCBCR444 ; 
 void* COLOR_YCBCR601 ; 
 void* COLOR_YCBCR709 ; 
 int DRM_COLOR_FORMAT_YCRCB422 ; 
 int DRM_COLOR_FORMAT_YCRCB444 ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 void* VESA ; 
 int drm_match_cea_mode (struct drm_display_mode const*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 

__attribute__((used)) static void analogix_dp_bridge_mode_set(struct drm_bridge *bridge,
				const struct drm_display_mode *orig_mode,
				const struct drm_display_mode *mode)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	struct drm_display_info *display_info = &dp->connector.display_info;
	struct video_info *video = &dp->video_info;
	struct device_node *dp_node = dp->dev->of_node;
	int vic;

	/* Input video interlaces & hsync pol & vsync pol */
	video->interlaced = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);
	video->v_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NVSYNC);
	video->h_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NHSYNC);

	/* Input video dynamic_range & colorimetry */
	vic = drm_match_cea_mode(mode);
	if ((vic == 6) || (vic == 7) || (vic == 21) || (vic == 22) ||
	    (vic == 2) || (vic == 3) || (vic == 17) || (vic == 18)) {
		video->dynamic_range = CEA;
		video->ycbcr_coeff = COLOR_YCBCR601;
	} else if (vic) {
		video->dynamic_range = CEA;
		video->ycbcr_coeff = COLOR_YCBCR709;
	} else {
		video->dynamic_range = VESA;
		video->ycbcr_coeff = COLOR_YCBCR709;
	}

	/* Input vide bpc and color_formats */
	switch (display_info->bpc) {
	case 12:
		video->color_depth = COLOR_12;
		break;
	case 10:
		video->color_depth = COLOR_10;
		break;
	case 8:
		video->color_depth = COLOR_8;
		break;
	case 6:
		video->color_depth = COLOR_6;
		break;
	default:
		video->color_depth = COLOR_8;
		break;
	}
	if (display_info->color_formats & DRM_COLOR_FORMAT_YCRCB444)
		video->color_space = COLOR_YCBCR444;
	else if (display_info->color_formats & DRM_COLOR_FORMAT_YCRCB422)
		video->color_space = COLOR_YCBCR422;
	else
		video->color_space = COLOR_RGB;

	/*
	 * NOTE: those property parsing code is used for providing backward
	 * compatibility for samsung platform.
	 * Due to we used the "of_property_read_u32" interfaces, when this
	 * property isn't present, the "video_info" can keep the original
	 * values and wouldn't be modified.
	 */
	of_property_read_u32(dp_node, "samsung,color-space",
			     &video->color_space);
	of_property_read_u32(dp_node, "samsung,dynamic-range",
			     &video->dynamic_range);
	of_property_read_u32(dp_node, "samsung,ycbcr-coeff",
			     &video->ycbcr_coeff);
	of_property_read_u32(dp_node, "samsung,color-depth",
			     &video->color_depth);
	if (of_property_read_bool(dp_node, "hsync-active-high"))
		video->h_sync_polarity = true;
	if (of_property_read_bool(dp_node, "vsync-active-high"))
		video->v_sync_polarity = true;
	if (of_property_read_bool(dp_node, "interlaced"))
		video->interlaced = true;
}