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
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_BEGIN (struct drm_device*,struct drm_modeset_acquire_ctx,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_END (struct drm_modeset_acquire_ctx,int) ; 
 int drm_atomic_helper_commit_duplicated_state (struct drm_atomic_state*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 

int drm_atomic_helper_resume(struct drm_device *dev,
			     struct drm_atomic_state *state)
{
	struct drm_modeset_acquire_ctx ctx;
	int err;

	drm_mode_config_reset(dev);

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, err);

	err = drm_atomic_helper_commit_duplicated_state(state, &ctx);

	DRM_MODESET_LOCK_ALL_END(ctx, err);
	drm_atomic_state_put(state);

	return err;
}