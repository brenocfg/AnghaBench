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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_atomic_state {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool skl_needs_memory_bw_wa(struct intel_atomic_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->base.dev);

	if (IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv))
		return true;

	return false;
}