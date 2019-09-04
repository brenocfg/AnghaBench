#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_overlay {TYPE_2__* vma; TYPE_2__* old_vma; int /*<<< orphan*/  i915; TYPE_1__* crtc; } ;
struct i915_vma {int /*<<< orphan*/ * obj; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_5__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_4__ {int pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_FRONTBUFFER_OVERLAY (int) ; 
 int /*<<< orphan*/  WARN_ON (TYPE_2__*) ; 
 int /*<<< orphan*/  i915_gem_track_fb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* i915_vma_get (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flip_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_overlay_flip_prepare(struct intel_overlay *overlay,
				       struct i915_vma *vma)
{
	enum pipe pipe = overlay->crtc->pipe;

	WARN_ON(overlay->old_vma);

	i915_gem_track_fb(overlay->vma ? overlay->vma->obj : NULL,
			  vma ? vma->obj : NULL,
			  INTEL_FRONTBUFFER_OVERLAY(pipe));

	intel_frontbuffer_flip_prepare(overlay->i915,
				       INTEL_FRONTBUFFER_OVERLAY(pipe));

	overlay->old_vma = overlay->vma;
	if (vma)
		overlay->vma = i915_vma_get(vma);
	else
		overlay->vma = NULL;
}