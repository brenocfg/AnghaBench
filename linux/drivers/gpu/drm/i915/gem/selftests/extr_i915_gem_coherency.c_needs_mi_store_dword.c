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
struct drm_i915_private {int /*<<< orphan*/ * engine; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_ENGINE (struct drm_i915_private*,size_t) ; 
 size_t RCS0 ; 
 int intel_engine_can_store_dword (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_gt_is_wedged (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool needs_mi_store_dword(struct drm_i915_private *i915)
{
	if (intel_gt_is_wedged(&i915->gt))
		return false;

	if (!HAS_ENGINE(i915, RCS0))
		return false;

	return intel_engine_can_store_dword(i915->engine[RCS0]);
}