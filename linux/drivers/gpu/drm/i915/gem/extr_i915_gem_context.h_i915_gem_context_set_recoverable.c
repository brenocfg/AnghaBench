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
struct i915_gem_context {int /*<<< orphan*/  user_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCONTEXT_RECOVERABLE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void i915_gem_context_set_recoverable(struct i915_gem_context *ctx)
{
	set_bit(UCONTEXT_RECOVERABLE, &ctx->user_flags);
}