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
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_REFLECT_Y ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (struct drm_plane*,int,int) ; 

__attribute__((used)) static void mdp5_plane_install_rotation_property(struct drm_device *dev,
		struct drm_plane *plane)
{
	drm_plane_create_rotation_property(plane,
					   DRM_MODE_ROTATE_0,
					   DRM_MODE_ROTATE_0 |
					   DRM_MODE_ROTATE_180 |
					   DRM_MODE_REFLECT_X |
					   DRM_MODE_REFLECT_Y);
}