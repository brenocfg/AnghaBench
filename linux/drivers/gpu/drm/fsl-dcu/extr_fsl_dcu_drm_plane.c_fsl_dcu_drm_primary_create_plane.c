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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_dcu_drm_plane_formats ; 
 int /*<<< orphan*/  fsl_dcu_drm_plane_funcs ; 
 int /*<<< orphan*/  fsl_dcu_drm_plane_helper_funcs ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_plane *fsl_dcu_drm_primary_create_plane(struct drm_device *dev)
{
	struct drm_plane *primary;
	int ret;

	primary = kzalloc(sizeof(*primary), GFP_KERNEL);
	if (!primary) {
		DRM_DEBUG_KMS("Failed to allocate primary plane\n");
		return NULL;
	}

	/* possible_crtc's will be filled in later by crtc_init */
	ret = drm_universal_plane_init(dev, primary, 0,
				       &fsl_dcu_drm_plane_funcs,
				       fsl_dcu_drm_plane_formats,
				       ARRAY_SIZE(fsl_dcu_drm_plane_formats),
				       NULL, DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret) {
		kfree(primary);
		primary = NULL;
	}
	drm_plane_helper_add(primary, &fsl_dcu_drm_plane_helper_funcs);

	return primary;
}