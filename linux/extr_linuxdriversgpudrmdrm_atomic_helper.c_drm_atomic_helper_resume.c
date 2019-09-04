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
 int EDEADLK ; 
 int drm_atomic_helper_commit_duplicated_state (struct drm_atomic_state*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 

int drm_atomic_helper_resume(struct drm_device *dev,
			     struct drm_atomic_state *state)
{
	struct drm_modeset_acquire_ctx ctx;
	int err;

	drm_mode_config_reset(dev);

	drm_modeset_acquire_init(&ctx, 0);
	while (1) {
		err = drm_modeset_lock_all_ctx(dev, &ctx);
		if (err)
			goto out;

		err = drm_atomic_helper_commit_duplicated_state(state, &ctx);
out:
		if (err != -EDEADLK)
			break;

		drm_modeset_backoff(&ctx);
	}

	drm_atomic_state_put(state);
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return err;
}