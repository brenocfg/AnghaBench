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
struct drm_modeset_lock {int dummy; } ;
struct drm_modeset_acquire_ctx {int /*<<< orphan*/  interruptible; struct drm_modeset_lock* contended; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int modeset_lock (struct drm_modeset_lock*,struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ,int) ; 

int drm_modeset_backoff(struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_modeset_lock *contended = ctx->contended;

	ctx->contended = NULL;

	if (WARN_ON(!contended))
		return 0;

	drm_modeset_drop_locks(ctx);

	return modeset_lock(contended, ctx, ctx->interruptible, true);
}