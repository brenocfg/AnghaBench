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
struct preempt_smoke {int /*<<< orphan*/  prng; int /*<<< orphan*/  ncontext; struct i915_gem_context** contexts; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 size_t i915_prandom_u32_max_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_gem_context *smoke_context(struct preempt_smoke *smoke)
{
	return smoke->contexts[i915_prandom_u32_max_state(smoke->ncontext,
							  &smoke->prng)];
}