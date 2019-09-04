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
struct drm_modeset_lock {int /*<<< orphan*/  mutex; } ;
struct drm_modeset_acquire_ctx {int /*<<< orphan*/  interruptible; } ;

/* Variables and functions */
 int modeset_lock (struct drm_modeset_lock*,struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ww_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_modeset_lock(struct drm_modeset_lock *lock,
		struct drm_modeset_acquire_ctx *ctx)
{
	if (ctx)
		return modeset_lock(lock, ctx, ctx->interruptible, false);

	ww_mutex_lock(&lock->mutex, NULL);
	return 0;
}