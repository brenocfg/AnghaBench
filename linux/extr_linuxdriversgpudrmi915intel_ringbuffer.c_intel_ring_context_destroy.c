#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_context {TYPE_1__* state; int /*<<< orphan*/  pin_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ring_context_destroy(struct intel_context *ce)
{
	GEM_BUG_ON(ce->pin_count);

	if (!ce->state)
		return;

	GEM_BUG_ON(i915_gem_object_is_active(ce->state->obj));
	i915_gem_object_put(ce->state->obj);
}