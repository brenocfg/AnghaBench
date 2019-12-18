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
struct drm_i915_private {int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ggtt_restore_mappings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_private_pat (struct drm_i915_private*) ; 

void i915_gem_restore_gtt_mappings(struct drm_i915_private *i915)
{
	ggtt_restore_mappings(&i915->ggtt);

	if (INTEL_GEN(i915) >= 8)
		setup_private_pat(i915);
}