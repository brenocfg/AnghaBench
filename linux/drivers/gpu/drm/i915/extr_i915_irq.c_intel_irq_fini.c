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
struct TYPE_2__ {int /*<<< orphan*/ * remap_info; } ;
struct drm_i915_private {TYPE_1__ l3_parity; } ;

/* Variables and functions */
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 int MAX_L3_SLICES ; 
 int /*<<< orphan*/  i945gm_vblank_work_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void intel_irq_fini(struct drm_i915_private *i915)
{
	int i;

	if (IS_I945GM(i915))
		i945gm_vblank_work_fini(i915);

	for (i = 0; i < MAX_L3_SLICES; ++i)
		kfree(i915->l3_parity.remap_info[i]);
}