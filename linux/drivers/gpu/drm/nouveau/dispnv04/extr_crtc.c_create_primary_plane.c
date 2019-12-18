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
 int /*<<< orphan*/  drm_primary_helper_funcs ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modeset_formats ; 

__attribute__((used)) static struct drm_plane *
create_primary_plane(struct drm_device *dev)
{
        struct drm_plane *primary;
        int ret;

        primary = kzalloc(sizeof(*primary), GFP_KERNEL);
        if (primary == NULL) {
                DRM_DEBUG_KMS("Failed to allocate primary plane\n");
                return NULL;
        }

        /* possible_crtc's will be filled in later by crtc_init */
        ret = drm_universal_plane_init(dev, primary, 0,
                                       &drm_primary_helper_funcs,
                                       modeset_formats,
                                       ARRAY_SIZE(modeset_formats), NULL,
                                       DRM_PLANE_TYPE_PRIMARY, NULL);
        if (ret) {
                kfree(primary);
                primary = NULL;
        }

        return primary;
}