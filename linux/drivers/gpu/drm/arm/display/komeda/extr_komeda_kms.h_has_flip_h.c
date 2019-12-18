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
 int DRM_MODE_REFLECT_MASK ; 
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_REFLECT_Y ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_90 ; 
 int drm_rotation_simplify (int,int) ; 

__attribute__((used)) static inline bool has_flip_h(u32 rot)
{
	u32 rotation = drm_rotation_simplify(rot,
					     DRM_MODE_ROTATE_0 |
					     DRM_MODE_ROTATE_90 |
					     DRM_MODE_REFLECT_MASK);

	if (rotation & DRM_MODE_ROTATE_90)
		return !!(rotation & DRM_MODE_REFLECT_Y);
	else
		return !!(rotation & DRM_MODE_REFLECT_X);
}