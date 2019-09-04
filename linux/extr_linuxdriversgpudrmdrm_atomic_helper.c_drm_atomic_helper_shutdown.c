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
 int EDEADLK ; 
 int __drm_atomic_helper_disable_all (struct drm_device*,struct drm_modeset_acquire_ctx*,int) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 

void drm_atomic_helper_shutdown(struct drm_device *dev)
{
	struct drm_modeset_acquire_ctx ctx;
	int ret;

	drm_modeset_acquire_init(&ctx, 0);
	while (1) {
		ret = drm_modeset_lock_all_ctx(dev, &ctx);
		if (!ret)
			ret = __drm_atomic_helper_disable_all(dev, &ctx, true);

		if (ret != -EDEADLK)
			break;

		drm_modeset_backoff(&ctx);
	}

	if (ret)
		DRM_ERROR("Disabling all crtc's during unload failed with %i\n", ret);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
}