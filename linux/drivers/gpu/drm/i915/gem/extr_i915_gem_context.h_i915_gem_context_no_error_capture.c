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
 int /*<<< orphan*/  UCONTEXT_NO_ERROR_CAPTURE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool i915_gem_context_no_error_capture(const struct i915_gem_context *ctx)
{
	return test_bit(UCONTEXT_NO_ERROR_CAPTURE, &ctx->user_flags);
}