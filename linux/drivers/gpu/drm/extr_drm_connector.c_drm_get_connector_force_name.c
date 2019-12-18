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
typedef  enum drm_connector_force { ____Placeholder_drm_connector_force } drm_connector_force ;

/* Variables and functions */
#define  DRM_FORCE_OFF 131 
#define  DRM_FORCE_ON 130 
#define  DRM_FORCE_ON_DIGITAL 129 
#define  DRM_FORCE_UNSPECIFIED 128 

const char *drm_get_connector_force_name(enum drm_connector_force force)
{
	switch (force) {
	case DRM_FORCE_UNSPECIFIED:
		return "unspecified";
	case DRM_FORCE_OFF:
		return "off";
	case DRM_FORCE_ON:
		return "on";
	case DRM_FORCE_ON_DIGITAL:
		return "digital";
	default:
		return "unknown";
	}
}