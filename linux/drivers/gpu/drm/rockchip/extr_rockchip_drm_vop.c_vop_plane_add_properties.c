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
struct vop_win_data {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 scalar_t__ VOP_WIN_HAS_REG (struct vop_win_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (struct drm_plane*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  x_mir_en ; 
 int /*<<< orphan*/  y_mir_en ; 

__attribute__((used)) static void vop_plane_add_properties(struct drm_plane *plane,
				     const struct vop_win_data *win_data)
{
	unsigned int flags = 0;

	flags |= VOP_WIN_HAS_REG(win_data, x_mir_en) ? DRM_MODE_REFLECT_X : 0;
	flags |= VOP_WIN_HAS_REG(win_data, y_mir_en) ? DRM_MODE_REFLECT_Y : 0;
	if (flags)
		drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
						   DRM_MODE_ROTATE_0 | flags);
}