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
struct i915_gem_context {int /*<<< orphan*/  name; } ;
struct drm_i915_file_private {int /*<<< orphan*/  ban_score; int /*<<< orphan*/  hang_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ I915_CLIENT_FAST_HANG_JIFFIES ; 
 unsigned int I915_CLIENT_SCORE_CONTEXT_BAN ; 
 scalar_t__ I915_CLIENT_SCORE_HANG_FAST ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ i915_gem_context_is_banned (struct i915_gem_context const*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void client_mark_guilty(struct drm_i915_file_private *file_priv,
			       const struct i915_gem_context *ctx)
{
	unsigned int score;
	unsigned long prev_hang;

	if (i915_gem_context_is_banned(ctx))
		score = I915_CLIENT_SCORE_CONTEXT_BAN;
	else
		score = 0;

	prev_hang = xchg(&file_priv->hang_timestamp, jiffies);
	if (time_before(jiffies, prev_hang + I915_CLIENT_FAST_HANG_JIFFIES))
		score += I915_CLIENT_SCORE_HANG_FAST;

	if (score) {
		atomic_add(score, &file_priv->ban_score);

		DRM_DEBUG_DRIVER("client %s: gained %u ban score, now %u\n",
				 ctx->name, score,
				 atomic_read(&file_priv->ban_score));
	}
}