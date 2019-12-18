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
typedef  enum drm_dp_dual_mode_type { ____Placeholder_drm_dp_dual_mode_type } drm_dp_dual_mode_type ;

/* Variables and functions */
#define  DRM_DP_DUAL_MODE_LSPCON 133 
#define  DRM_DP_DUAL_MODE_NONE 132 
#define  DRM_DP_DUAL_MODE_TYPE1_DVI 131 
#define  DRM_DP_DUAL_MODE_TYPE1_HDMI 130 
#define  DRM_DP_DUAL_MODE_TYPE2_DVI 129 
#define  DRM_DP_DUAL_MODE_TYPE2_HDMI 128 
 int DRM_DP_DUAL_MODE_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

const char *drm_dp_get_dual_mode_type_name(enum drm_dp_dual_mode_type type)
{
	switch (type) {
	case DRM_DP_DUAL_MODE_NONE:
		return "none";
	case DRM_DP_DUAL_MODE_TYPE1_DVI:
		return "type 1 DVI";
	case DRM_DP_DUAL_MODE_TYPE1_HDMI:
		return "type 1 HDMI";
	case DRM_DP_DUAL_MODE_TYPE2_DVI:
		return "type 2 DVI";
	case DRM_DP_DUAL_MODE_TYPE2_HDMI:
		return "type 2 HDMI";
	case DRM_DP_DUAL_MODE_LSPCON:
		return "lspcon";
	default:
		WARN_ON(type != DRM_DP_DUAL_MODE_UNKNOWN);
		return "unknown";
	}
}