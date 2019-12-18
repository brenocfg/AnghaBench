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
 int EINVAL ; 
 struct drm_atomic_state* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_atomic_state*) ; 
 int drm_atomic_helper_disable_all (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 struct drm_atomic_state* drm_atomic_helper_duplicate_state (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 

struct drm_atomic_state *drm_atomic_helper_suspend(struct drm_device *dev)
{
	struct drm_modeset_acquire_ctx ctx;
	struct drm_atomic_state *state;
	int err;

	/* This can never be returned, but it makes the compiler happy */
	state = ERR_PTR(-EINVAL);

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, err);

	state = drm_atomic_helper_duplicate_state(dev, &ctx);
	if (IS_ERR(state))
		goto unlock;

	err = drm_atomic_helper_disable_all(dev, &ctx);
	if (err < 0) {
		drm_atomic_state_put(state);
		state = ERR_PTR(err);
		goto unlock;
	}

unlock:
	DRM_MODESET_LOCK_ALL_END(ctx, err);
	if (err)
		return ERR_PTR(err);

	return state;
}