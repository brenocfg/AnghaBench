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

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 unsigned int DRM_MODE_ROTATE_MASK ; 
 int MASK_XY_FLIP ; 
 int MASK_X_INVERT ; 
 int MASK_Y_INVERT ; 

__attribute__((used)) static u32 drm_rotation_to_tiler(unsigned int drm_rot)
{
	u32 orient;

	switch (drm_rot & DRM_MODE_ROTATE_MASK) {
	default:
	case DRM_MODE_ROTATE_0:
		orient = 0;
		break;
	case DRM_MODE_ROTATE_90:
		orient = MASK_XY_FLIP | MASK_X_INVERT;
		break;
	case DRM_MODE_ROTATE_180:
		orient = MASK_X_INVERT | MASK_Y_INVERT;
		break;
	case DRM_MODE_ROTATE_270:
		orient = MASK_XY_FLIP | MASK_Y_INVERT;
		break;
	}

	if (drm_rot & DRM_MODE_REFLECT_X)
		orient ^= MASK_X_INVERT;

	if (drm_rot & DRM_MODE_REFLECT_Y)
		orient ^= MASK_Y_INVERT;

	return orient;
}