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
struct i915_gem_context {unsigned long* hang_timestamp; int /*<<< orphan*/  file_priv; int /*<<< orphan*/  guilty_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 scalar_t__ CONTEXT_FAST_HANG_JIFFIES ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_mark_guilty (int /*<<< orphan*/ ,struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_is_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_is_recoverable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_banned (struct i915_gem_context*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 

__attribute__((used)) static bool context_mark_guilty(struct i915_gem_context *ctx)
{
	unsigned long prev_hang;
	bool banned;
	int i;

	atomic_inc(&ctx->guilty_count);

	/* Cool contexts are too cool to be banned! (Used for reset testing.) */
	if (!i915_gem_context_is_bannable(ctx))
		return false;

	/* Record the timestamp for the last N hangs */
	prev_hang = ctx->hang_timestamp[0];
	for (i = 0; i < ARRAY_SIZE(ctx->hang_timestamp) - 1; i++)
		ctx->hang_timestamp[i] = ctx->hang_timestamp[i + 1];
	ctx->hang_timestamp[i] = jiffies;

	/* If we have hung N+1 times in rapid succession, we ban the context! */
	banned = !i915_gem_context_is_recoverable(ctx);
	if (time_before(jiffies, prev_hang + CONTEXT_FAST_HANG_JIFFIES))
		banned = true;
	if (banned) {
		DRM_DEBUG_DRIVER("context %s: guilty %d, banned\n",
				 ctx->name, atomic_read(&ctx->guilty_count));
		i915_gem_context_set_banned(ctx);
	}

	if (!IS_ERR_OR_NULL(ctx->file_priv))
		client_mark_guilty(ctx->file_priv, ctx);

	return banned;
}