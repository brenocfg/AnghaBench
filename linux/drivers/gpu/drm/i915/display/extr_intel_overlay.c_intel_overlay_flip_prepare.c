#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct intel_overlay {TYPE_4__* vma; TYPE_4__* old_vma; int /*<<< orphan*/  i915; TYPE_3__* crtc; } ;
struct i915_vma {TYPE_2__* obj; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_9__ {TYPE_1__* obj; } ;
struct TYPE_8__ {int pipe; } ;
struct TYPE_7__ {int /*<<< orphan*/ * frontbuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/ * frontbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_FRONTBUFFER_OVERLAY (int) ; 
 int /*<<< orphan*/  WARN_ON (TYPE_4__*) ; 
 TYPE_4__* i915_vma_get (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flip_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_frontbuffer_track (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_overlay_flip_prepare(struct intel_overlay *overlay,
				       struct i915_vma *vma)
{
	enum pipe pipe = overlay->crtc->pipe;

	WARN_ON(overlay->old_vma);

	intel_frontbuffer_track(overlay->vma ? overlay->vma->obj->frontbuffer : NULL,
				vma ? vma->obj->frontbuffer : NULL,
				INTEL_FRONTBUFFER_OVERLAY(pipe));

	intel_frontbuffer_flip_prepare(overlay->i915,
				       INTEL_FRONTBUFFER_OVERLAY(pipe));

	overlay->old_vma = overlay->vma;
	if (vma)
		overlay->vma = i915_vma_get(vma);
	else
		overlay->vma = NULL;
}