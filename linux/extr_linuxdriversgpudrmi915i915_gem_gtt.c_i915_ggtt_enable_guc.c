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
struct TYPE_2__ {scalar_t__ invalidate; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ gen6_ggtt_invalidate ; 
 scalar_t__ guc_ggtt_invalidate ; 
 int /*<<< orphan*/  i915_ggtt_invalidate (struct drm_i915_private*) ; 

void i915_ggtt_enable_guc(struct drm_i915_private *i915)
{
	GEM_BUG_ON(i915->ggtt.invalidate != gen6_ggtt_invalidate);

	i915->ggtt.invalidate = guc_ggtt_invalidate;

	i915_ggtt_invalidate(i915);
}