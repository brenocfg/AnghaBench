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
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
#define  DP_SDP_PPS 134 
#define  DP_SDP_VSC 133 
 int /*<<< orphan*/  GLK_TVIDEO_DIP_DRM_DATA (int,int) ; 
#define  HDMI_INFOFRAME_TYPE_AVI 132 
#define  HDMI_INFOFRAME_TYPE_DRM 131 
#define  HDMI_INFOFRAME_TYPE_SPD 130 
#define  HDMI_INFOFRAME_TYPE_VENDOR 129 
#define  HDMI_PACKET_TYPE_GAMUT_METADATA 128 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_AVI_DATA (int,int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_GMP_DATA (int,int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_SPD_DATA (int,int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_VSC_DATA (int,int) ; 
 int /*<<< orphan*/  HSW_TVIDEO_DIP_VS_DATA (int,int) ; 
 int /*<<< orphan*/  ICL_VIDEO_DIP_PPS_DATA (int,int) ; 
 int /*<<< orphan*/  INVALID_MMIO_REG ; 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 

__attribute__((used)) static i915_reg_t
hsw_dip_data_reg(struct drm_i915_private *dev_priv,
		 enum transcoder cpu_transcoder,
		 unsigned int type,
		 int i)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		return HSW_TVIDEO_DIP_GMP_DATA(cpu_transcoder, i);
	case DP_SDP_VSC:
		return HSW_TVIDEO_DIP_VSC_DATA(cpu_transcoder, i);
	case DP_SDP_PPS:
		return ICL_VIDEO_DIP_PPS_DATA(cpu_transcoder, i);
	case HDMI_INFOFRAME_TYPE_AVI:
		return HSW_TVIDEO_DIP_AVI_DATA(cpu_transcoder, i);
	case HDMI_INFOFRAME_TYPE_SPD:
		return HSW_TVIDEO_DIP_SPD_DATA(cpu_transcoder, i);
	case HDMI_INFOFRAME_TYPE_VENDOR:
		return HSW_TVIDEO_DIP_VS_DATA(cpu_transcoder, i);
	case HDMI_INFOFRAME_TYPE_DRM:
		return GLK_TVIDEO_DIP_DRM_DATA(cpu_transcoder, i);
	default:
		MISSING_CASE(type);
		return INVALID_MMIO_REG;
	}
}