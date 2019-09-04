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
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int DRM_MODE_CONNECTOR_DVID ; 
 int DRM_MODE_CONNECTOR_DisplayPort ; 
 int DRM_MODE_CONNECTOR_HDMIA ; 
 int DRM_MODE_CONNECTOR_Unknown ; 
 int DRM_MODE_CONNECTOR_VGA ; 
 int DRM_MODE_CONNECTOR_VIRTUAL ; 
 int DRM_MODE_CONNECTOR_eDP ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 135 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 134 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 133 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 132 
#define  SIGNAL_TYPE_EDP 131 
#define  SIGNAL_TYPE_HDMI_TYPE_A 130 
#define  SIGNAL_TYPE_RGB 129 
#define  SIGNAL_TYPE_VIRTUAL 128 

__attribute__((used)) static int to_drm_connector_type(enum signal_type st)
{
	switch (st) {
	case SIGNAL_TYPE_HDMI_TYPE_A:
		return DRM_MODE_CONNECTOR_HDMIA;
	case SIGNAL_TYPE_EDP:
		return DRM_MODE_CONNECTOR_eDP;
	case SIGNAL_TYPE_RGB:
		return DRM_MODE_CONNECTOR_VGA;
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		return DRM_MODE_CONNECTOR_DisplayPort;
	case SIGNAL_TYPE_DVI_DUAL_LINK:
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
		return DRM_MODE_CONNECTOR_DVID;
	case SIGNAL_TYPE_VIRTUAL:
		return DRM_MODE_CONNECTOR_VIRTUAL;

	default:
		return DRM_MODE_CONNECTOR_Unknown;
	}
}