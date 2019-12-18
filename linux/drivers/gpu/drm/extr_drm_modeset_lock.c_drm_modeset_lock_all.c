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
struct drm_modeset_acquire_ctx {int /*<<< orphan*/  ww_ctx; } ;
struct drm_mode_config {int acquire_ctx; int /*<<< orphan*/  mutex; } ;
struct drm_device {struct drm_mode_config mode_config; } ;

/* Variables and functions */
 int EDEADLK ; 
 int GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_warn_on_modeset_not_all_locked (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct drm_modeset_acquire_ctx*) ; 
 struct drm_modeset_acquire_ctx* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ww_acquire_done (int /*<<< orphan*/ *) ; 

void drm_modeset_lock_all(struct drm_device *dev)
{
	struct drm_mode_config *config = &dev->mode_config;
	struct drm_modeset_acquire_ctx *ctx;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL | __GFP_NOFAIL);
	if (WARN_ON(!ctx))
		return;

	mutex_lock(&config->mutex);

	drm_modeset_acquire_init(ctx, 0);

retry:
	ret = drm_modeset_lock_all_ctx(dev, ctx);
	if (ret < 0) {
		if (ret == -EDEADLK) {
			drm_modeset_backoff(ctx);
			goto retry;
		}

		drm_modeset_acquire_fini(ctx);
		kfree(ctx);
		return;
	}
	ww_acquire_done(&ctx->ww_ctx);

	WARN_ON(config->acquire_ctx);

	/*
	 * We hold the locks now, so it is safe to stash the acquisition
	 * context for drm_modeset_unlock_all().
	 */
	config->acquire_ctx = ctx;

	drm_warn_on_modeset_not_all_locked(dev);
}