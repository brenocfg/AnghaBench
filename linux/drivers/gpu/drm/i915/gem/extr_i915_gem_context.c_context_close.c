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
struct i915_gem_context {int /*<<< orphan*/  mutex; int /*<<< orphan*/  file_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_put (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_closed (struct i915_gem_context*) ; 
 int /*<<< orphan*/  lut_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_hw_id (struct i915_gem_context*) ; 

__attribute__((used)) static void context_close(struct i915_gem_context *ctx)
{
	mutex_lock(&ctx->mutex);

	i915_gem_context_set_closed(ctx);
	ctx->file_priv = ERR_PTR(-EBADF);

	/*
	 * This context will never again be assinged to HW, so we can
	 * reuse its ID for the next context.
	 */
	release_hw_id(ctx);

	/*
	 * The LUT uses the VMA as a backpointer to unref the object,
	 * so we need to clear the LUT before we close all the VMA (inside
	 * the ppgtt).
	 */
	lut_close(ctx);

	mutex_unlock(&ctx->mutex);
	i915_gem_context_put(ctx);
}