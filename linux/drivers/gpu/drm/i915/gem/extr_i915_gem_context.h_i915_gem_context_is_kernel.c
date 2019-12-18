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
struct i915_gem_context {int /*<<< orphan*/  file_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline bool i915_gem_context_is_kernel(struct i915_gem_context *ctx)
{
	return !ctx->file_priv;
}