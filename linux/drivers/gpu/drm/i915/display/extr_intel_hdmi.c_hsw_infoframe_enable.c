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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  DP_SDP_PPS 135 
#define  DP_SDP_VSC 134 
#define  HDMI_INFOFRAME_TYPE_AVI 133 
#define  HDMI_INFOFRAME_TYPE_DRM 132 
#define  HDMI_INFOFRAME_TYPE_SPD 131 
#define  HDMI_INFOFRAME_TYPE_VENDOR 130 
#define  HDMI_PACKET_TYPE_GAMUT_METADATA 129 
#define  HDMI_PACKET_TYPE_GENERAL_CONTROL 128 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 
 int /*<<< orphan*/  VDIP_ENABLE_PPS ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_AVI_HSW ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_DRM_GLK ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_GCP_HSW ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_GMP_HSW ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_SPD_HSW ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_VSC_HSW ; 
 int /*<<< orphan*/  VIDEO_DIP_ENABLE_VS_HSW ; 

__attribute__((used)) static u32 hsw_infoframe_enable(unsigned int type)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GENERAL_CONTROL:
		return VIDEO_DIP_ENABLE_GCP_HSW;
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		return VIDEO_DIP_ENABLE_GMP_HSW;
	case DP_SDP_VSC:
		return VIDEO_DIP_ENABLE_VSC_HSW;
	case DP_SDP_PPS:
		return VDIP_ENABLE_PPS;
	case HDMI_INFOFRAME_TYPE_AVI:
		return VIDEO_DIP_ENABLE_AVI_HSW;
	case HDMI_INFOFRAME_TYPE_SPD:
		return VIDEO_DIP_ENABLE_SPD_HSW;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		return VIDEO_DIP_ENABLE_VS_HSW;
	case HDMI_INFOFRAME_TYPE_DRM:
		return VIDEO_DIP_ENABLE_DRM_GLK;
	default:
		MISSING_CASE(type);
		return 0;
	}
}