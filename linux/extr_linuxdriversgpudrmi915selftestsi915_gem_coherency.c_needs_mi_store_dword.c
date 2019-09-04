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
struct drm_i915_private {int /*<<< orphan*/ * engine; int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 size_t RCS ; 
 scalar_t__ i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int intel_engine_can_store_dword (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool needs_mi_store_dword(struct drm_i915_private *i915)
{
	if (i915_terminally_wedged(&i915->gpu_error))
		return false;

	return intel_engine_can_store_dword(i915->engine[RCS]);
}