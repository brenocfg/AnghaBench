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
struct intel_overlay {TYPE_2__* i915; int /*<<< orphan*/  last_flip; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int i915_gem_active_retire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_overlay_recover_from_interrupt(struct intel_overlay *overlay)
{
	return i915_gem_active_retire(&overlay->last_flip,
				      &overlay->i915->drm.struct_mutex);
}