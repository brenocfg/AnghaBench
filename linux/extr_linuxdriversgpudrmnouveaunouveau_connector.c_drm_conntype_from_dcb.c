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
typedef  enum dcb_connector_type { ____Placeholder_dcb_connector_type } dcb_connector_type ;

/* Variables and functions */
#define  DCB_CONNECTOR_DMS59_0 145 
#define  DCB_CONNECTOR_DMS59_1 144 
#define  DCB_CONNECTOR_DMS59_DP0 143 
#define  DCB_CONNECTOR_DMS59_DP1 142 
#define  DCB_CONNECTOR_DP 141 
#define  DCB_CONNECTOR_DVI_D 140 
#define  DCB_CONNECTOR_DVI_I 139 
#define  DCB_CONNECTOR_HDMI_0 138 
#define  DCB_CONNECTOR_HDMI_1 137 
#define  DCB_CONNECTOR_HDMI_C 136 
#define  DCB_CONNECTOR_LVDS 135 
#define  DCB_CONNECTOR_LVDS_SPWG 134 
#define  DCB_CONNECTOR_TV_0 133 
#define  DCB_CONNECTOR_TV_1 132 
#define  DCB_CONNECTOR_TV_3 131 
#define  DCB_CONNECTOR_VGA 130 
#define  DCB_CONNECTOR_WFD 129 
#define  DCB_CONNECTOR_eDP 128 
 int DRM_MODE_CONNECTOR_DVID ; 
 int DRM_MODE_CONNECTOR_DVII ; 
 int DRM_MODE_CONNECTOR_DisplayPort ; 
 int DRM_MODE_CONNECTOR_HDMIA ; 
 int DRM_MODE_CONNECTOR_LVDS ; 
 int DRM_MODE_CONNECTOR_TV ; 
 int DRM_MODE_CONNECTOR_Unknown ; 
 int DRM_MODE_CONNECTOR_VGA ; 
 int DRM_MODE_CONNECTOR_VIRTUAL ; 
 int DRM_MODE_CONNECTOR_eDP ; 

__attribute__((used)) static int
drm_conntype_from_dcb(enum dcb_connector_type dcb)
{
	switch (dcb) {
	case DCB_CONNECTOR_VGA      : return DRM_MODE_CONNECTOR_VGA;
	case DCB_CONNECTOR_TV_0     :
	case DCB_CONNECTOR_TV_1     :
	case DCB_CONNECTOR_TV_3     : return DRM_MODE_CONNECTOR_TV;
	case DCB_CONNECTOR_DMS59_0  :
	case DCB_CONNECTOR_DMS59_1  :
	case DCB_CONNECTOR_DVI_I    : return DRM_MODE_CONNECTOR_DVII;
	case DCB_CONNECTOR_DVI_D    : return DRM_MODE_CONNECTOR_DVID;
	case DCB_CONNECTOR_LVDS     :
	case DCB_CONNECTOR_LVDS_SPWG: return DRM_MODE_CONNECTOR_LVDS;
	case DCB_CONNECTOR_DMS59_DP0:
	case DCB_CONNECTOR_DMS59_DP1:
	case DCB_CONNECTOR_DP       : return DRM_MODE_CONNECTOR_DisplayPort;
	case DCB_CONNECTOR_eDP      : return DRM_MODE_CONNECTOR_eDP;
	case DCB_CONNECTOR_HDMI_0   :
	case DCB_CONNECTOR_HDMI_1   :
	case DCB_CONNECTOR_HDMI_C   : return DRM_MODE_CONNECTOR_HDMIA;
	case DCB_CONNECTOR_WFD	    : return DRM_MODE_CONNECTOR_VIRTUAL;
	default:
		break;
	}

	return DRM_MODE_CONNECTOR_Unknown;
}