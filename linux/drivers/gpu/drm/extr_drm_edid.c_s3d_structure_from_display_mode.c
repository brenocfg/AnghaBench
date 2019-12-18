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
struct drm_display_mode {int flags; } ;
typedef  enum hdmi_3d_structure { ____Placeholder_hdmi_3d_structure } hdmi_3d_structure ;

/* Variables and functions */
#define  DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE 135 
#define  DRM_MODE_FLAG_3D_FRAME_PACKING 134 
#define  DRM_MODE_FLAG_3D_LINE_ALTERNATIVE 133 
#define  DRM_MODE_FLAG_3D_L_DEPTH 132 
#define  DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH 131 
 int DRM_MODE_FLAG_3D_MASK ; 
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL 130 
#define  DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF 129 
#define  DRM_MODE_FLAG_3D_TOP_AND_BOTTOM 128 
 int HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE ; 
 int HDMI_3D_STRUCTURE_FRAME_PACKING ; 
 int HDMI_3D_STRUCTURE_INVALID ; 
 int HDMI_3D_STRUCTURE_LINE_ALTERNATIVE ; 
 int HDMI_3D_STRUCTURE_L_DEPTH ; 
 int HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH ; 
 int HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL ; 
 int HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 
 int HDMI_3D_STRUCTURE_TOP_AND_BOTTOM ; 

__attribute__((used)) static enum hdmi_3d_structure
s3d_structure_from_display_mode(const struct drm_display_mode *mode)
{
	u32 layout = mode->flags & DRM_MODE_FLAG_3D_MASK;

	switch (layout) {
	case DRM_MODE_FLAG_3D_FRAME_PACKING:
		return HDMI_3D_STRUCTURE_FRAME_PACKING;
	case DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE:
		return HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE;
	case DRM_MODE_FLAG_3D_LINE_ALTERNATIVE:
		return HDMI_3D_STRUCTURE_LINE_ALTERNATIVE;
	case DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL:
		return HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL;
	case DRM_MODE_FLAG_3D_L_DEPTH:
		return HDMI_3D_STRUCTURE_L_DEPTH;
	case DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH:
		return HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH;
	case DRM_MODE_FLAG_3D_TOP_AND_BOTTOM:
		return HDMI_3D_STRUCTURE_TOP_AND_BOTTOM;
	case DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF:
		return HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF;
	default:
		return HDMI_3D_STRUCTURE_INVALID;
	}
}