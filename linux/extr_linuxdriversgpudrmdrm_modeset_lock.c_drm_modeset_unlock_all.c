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
struct drm_mode_config {int /*<<< orphan*/  mutex; struct drm_modeset_acquire_ctx* acquire_ctx; } ;
struct drm_device {struct drm_mode_config mode_config; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  kfree (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_modeset_unlock_all(struct drm_device *dev)
{
	struct drm_mode_config *config = &dev->mode_config;
	struct drm_modeset_acquire_ctx *ctx = config->acquire_ctx;

	if (WARN_ON(!ctx))
		return;

	config->acquire_ctx = NULL;
	drm_modeset_drop_locks(ctx);
	drm_modeset_acquire_fini(ctx);

	kfree(ctx);

	mutex_unlock(&dev->mode_config.mutex);
}