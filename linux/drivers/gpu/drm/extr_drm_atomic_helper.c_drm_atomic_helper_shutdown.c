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
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_BEGIN (struct drm_device*,struct drm_modeset_acquire_ctx,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_END (struct drm_modeset_acquire_ctx,int) ; 
 int drm_atomic_helper_disable_all (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 

void drm_atomic_helper_shutdown(struct drm_device *dev)
{
	struct drm_modeset_acquire_ctx ctx;
	int ret;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, ret);

	ret = drm_atomic_helper_disable_all(dev, &ctx);
	if (ret)
		DRM_ERROR("Disabling all crtc's during unload failed with %i\n", ret);

	DRM_MODESET_LOCK_ALL_END(ctx, ret);
}