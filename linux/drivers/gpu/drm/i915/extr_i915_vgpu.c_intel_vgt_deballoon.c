#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i915; } ;
struct i915_ggtt {TYPE_1__ vm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * space; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 TYPE_2__ bl_info ; 
 int /*<<< orphan*/  intel_vgpu_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgt_deballoon_space (struct i915_ggtt*,int /*<<< orphan*/ *) ; 

void intel_vgt_deballoon(struct i915_ggtt *ggtt)
{
	int i;

	if (!intel_vgpu_active(ggtt->vm.i915))
		return;

	DRM_DEBUG("VGT deballoon.\n");

	for (i = 0; i < 4; i++)
		vgt_deballoon_space(ggtt, &bl_info.space[i]);
}