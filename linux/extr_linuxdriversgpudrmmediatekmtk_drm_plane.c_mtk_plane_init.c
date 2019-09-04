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
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  formats ; 
 int /*<<< orphan*/  mtk_plane_funcs ; 
 int /*<<< orphan*/  mtk_plane_helper_funcs ; 

int mtk_plane_init(struct drm_device *dev, struct drm_plane *plane,
		   unsigned long possible_crtcs, enum drm_plane_type type)
{
	int err;

	err = drm_universal_plane_init(dev, plane, possible_crtcs,
				       &mtk_plane_funcs, formats,
				       ARRAY_SIZE(formats), NULL, type, NULL);
	if (err) {
		DRM_ERROR("failed to initialize plane\n");
		return err;
	}

	drm_plane_helper_add(plane, &mtk_plane_helper_funcs);

	return 0;
}