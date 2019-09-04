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
struct i915_gem_context {int /*<<< orphan*/  user_handle; } ;
struct drm_i915_file_private {int /*<<< orphan*/  context_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_close (struct i915_gem_context*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __destroy_hw_context(struct i915_gem_context *ctx,
				 struct drm_i915_file_private *file_priv)
{
	idr_remove(&file_priv->context_idr, ctx->user_handle);
	context_close(ctx);
}