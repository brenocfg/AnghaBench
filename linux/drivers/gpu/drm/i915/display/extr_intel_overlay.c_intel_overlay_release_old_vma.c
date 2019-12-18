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
struct intel_overlay {TYPE_1__* crtc; int /*<<< orphan*/  i915; int /*<<< orphan*/  old_vma; } ;
struct i915_vma {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_FRONTBUFFER_OVERLAY (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct i915_vma* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_from_display_plane (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_put (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flip_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_overlay_release_old_vma(struct intel_overlay *overlay)
{
	struct i915_vma *vma;

	vma = fetch_and_zero(&overlay->old_vma);
	if (WARN_ON(!vma))
		return;

	intel_frontbuffer_flip_complete(overlay->i915,
					INTEL_FRONTBUFFER_OVERLAY(overlay->crtc->pipe));

	i915_gem_object_unpin_from_display_plane(vma);
	i915_vma_put(vma);
}