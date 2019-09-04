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
struct i915_gem_context {int /*<<< orphan*/  file_priv; int /*<<< orphan*/  guilty_count; int /*<<< orphan*/  name; int /*<<< orphan*/  ban_score; } ;

/* Variables and functions */
 unsigned int CONTEXT_SCORE_BAN_THRESHOLD ; 
 int /*<<< orphan*/  CONTEXT_SCORE_GUILTY ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 unsigned int atomic_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_client_mark_guilty (int /*<<< orphan*/ ,struct i915_gem_context*) ; 
 int i915_gem_context_is_bannable (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_banned (struct i915_gem_context*) ; 

__attribute__((used)) static void i915_gem_context_mark_guilty(struct i915_gem_context *ctx)
{
	unsigned int score;
	bool banned, bannable;

	atomic_inc(&ctx->guilty_count);

	bannable = i915_gem_context_is_bannable(ctx);
	score = atomic_add_return(CONTEXT_SCORE_GUILTY, &ctx->ban_score);
	banned = score >= CONTEXT_SCORE_BAN_THRESHOLD;

	/* Cool contexts don't accumulate client ban score */
	if (!bannable)
		return;

	if (banned) {
		DRM_DEBUG_DRIVER("context %s: guilty %d, score %u, banned\n",
				 ctx->name, atomic_read(&ctx->guilty_count),
				 score);
		i915_gem_context_set_banned(ctx);
	}

	if (!IS_ERR_OR_NULL(ctx->file_priv))
		i915_gem_client_mark_guilty(ctx->file_priv, ctx);
}