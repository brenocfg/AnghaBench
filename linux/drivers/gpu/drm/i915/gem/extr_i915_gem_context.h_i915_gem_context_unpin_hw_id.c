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
struct i915_gem_context {int /*<<< orphan*/  hw_id_pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void i915_gem_context_unpin_hw_id(struct i915_gem_context *ctx)
{
	GEM_BUG_ON(atomic_read(&ctx->hw_id_pin_count) == 0u);
	atomic_dec(&ctx->hw_id_pin_count);
}