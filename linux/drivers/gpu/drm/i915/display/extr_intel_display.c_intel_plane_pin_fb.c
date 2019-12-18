#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {struct i915_vma* vma; int /*<<< orphan*/  flags; int /*<<< orphan*/  view; TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ id; TYPE_1__ base; } ;
struct i915_vma {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_6__ {scalar_t__ cursor_needs_physical; } ;
struct TYPE_8__ {TYPE_2__ display; } ;

/* Variables and functions */
 TYPE_4__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 scalar_t__ PLANE_CURSOR ; 
 int PTR_ERR (struct i915_vma*) ; 
 int i915_gem_object_attach_phys (struct drm_i915_gem_object*,int const) ; 
 int intel_cursor_alignment (struct drm_i915_private*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 struct i915_vma* intel_pin_and_fence_fb_obj (struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_plane_uses_fence (struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_plane_pin_fb(struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	struct drm_framebuffer *fb = plane_state->base.fb;
	struct i915_vma *vma;

	if (plane->id == PLANE_CURSOR &&
	    INTEL_INFO(dev_priv)->display.cursor_needs_physical) {
		struct drm_i915_gem_object *obj = intel_fb_obj(fb);
		const int align = intel_cursor_alignment(dev_priv);
		int err;

		err = i915_gem_object_attach_phys(obj, align);
		if (err)
			return err;
	}

	vma = intel_pin_and_fence_fb_obj(fb,
					 &plane_state->view,
					 intel_plane_uses_fence(plane_state),
					 &plane_state->flags);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	plane_state->vma = vma;

	return 0;
}