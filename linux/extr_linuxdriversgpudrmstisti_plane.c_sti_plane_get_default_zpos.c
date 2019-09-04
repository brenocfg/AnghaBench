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
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
#define  DRM_PLANE_TYPE_CURSOR 130 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 

__attribute__((used)) static int sti_plane_get_default_zpos(enum drm_plane_type type)
{
	switch (type) {
	case DRM_PLANE_TYPE_PRIMARY:
		return 0;
	case DRM_PLANE_TYPE_OVERLAY:
		return 1;
	case DRM_PLANE_TYPE_CURSOR:
		return 7;
	}
	return 0;
}