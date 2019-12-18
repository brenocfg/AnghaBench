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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  armada_primary_formats ; 
 int /*<<< orphan*/  armada_primary_plane_funcs ; 
 int /*<<< orphan*/  armada_primary_plane_helper_funcs ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int armada_drm_primary_plane_init(struct drm_device *drm,
	struct drm_plane *primary)
{
	int ret;

	drm_plane_helper_add(primary, &armada_primary_plane_helper_funcs);

	ret = drm_universal_plane_init(drm, primary, 0,
				       &armada_primary_plane_funcs,
				       armada_primary_formats,
				       ARRAY_SIZE(armada_primary_formats),
				       NULL,
				       DRM_PLANE_TYPE_PRIMARY, NULL);

	return ret;
}