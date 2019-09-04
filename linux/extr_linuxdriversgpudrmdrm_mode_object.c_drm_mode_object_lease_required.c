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
typedef  int uint32_t ;

/* Variables and functions */
#define  DRM_MODE_OBJECT_CONNECTOR 130 
#define  DRM_MODE_OBJECT_CRTC 129 
#define  DRM_MODE_OBJECT_PLANE 128 

bool drm_mode_object_lease_required(uint32_t type)
{
	switch(type) {
	case DRM_MODE_OBJECT_CRTC:
	case DRM_MODE_OBJECT_CONNECTOR:
	case DRM_MODE_OBJECT_PLANE:
		return true;
	default:
		return false;
	}
}