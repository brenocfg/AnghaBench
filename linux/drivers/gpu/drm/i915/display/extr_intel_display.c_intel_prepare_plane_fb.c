#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_crtc_state {int dummy; } ;
struct intel_atomic_state {int rps_interactive; int /*<<< orphan*/  commit_ready; } ;
struct drm_plane_state {struct dma_fence* fence; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; int /*<<< orphan*/  state; } ;
struct drm_plane {TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_3__ base; int /*<<< orphan*/  frontbuffer; } ;
struct drm_framebuffer {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_FENCE_TIMEOUT ; 
 int /*<<< orphan*/  ORIGIN_DIRTYFB ; 
 int /*<<< orphan*/  add_rps_boost_after_vblank (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_obj_bump_render_priority (struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int i915_sw_fence_await_dma_fence (int /*<<< orphan*/ *,struct dma_fence*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_sw_fence_await_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_plane_pin_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_rps_mark_interactive (struct drm_i915_private*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ needs_modeset (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_plane_state (struct drm_plane_state*) ; 

int
intel_prepare_plane_fb(struct drm_plane *plane,
		       struct drm_plane_state *new_state)
{
	struct intel_atomic_state *intel_state =
		to_intel_atomic_state(new_state->state);
	struct drm_i915_private *dev_priv = to_i915(plane->dev);
	struct drm_framebuffer *fb = new_state->fb;
	struct drm_i915_gem_object *obj = intel_fb_obj(fb);
	struct drm_i915_gem_object *old_obj = intel_fb_obj(plane->state->fb);
	int ret;

	if (old_obj) {
		struct intel_crtc_state *crtc_state =
			intel_atomic_get_new_crtc_state(intel_state,
							to_intel_crtc(plane->state->crtc));

		/* Big Hammer, we also need to ensure that any pending
		 * MI_WAIT_FOR_EVENT inside a user batch buffer on the
		 * current scanout is retired before unpinning the old
		 * framebuffer. Note that we rely on userspace rendering
		 * into the buffer attached to the pipe they are waiting
		 * on. If not, userspace generates a GPU hang with IPEHR
		 * point to the MI_WAIT_FOR_EVENT.
		 *
		 * This should only fail upon a hung GPU, in which case we
		 * can safely continue.
		 */
		if (needs_modeset(crtc_state)) {
			ret = i915_sw_fence_await_reservation(&intel_state->commit_ready,
							      old_obj->base.resv, NULL,
							      false, 0,
							      GFP_KERNEL);
			if (ret < 0)
				return ret;
		}
	}

	if (new_state->fence) { /* explicit fencing */
		ret = i915_sw_fence_await_dma_fence(&intel_state->commit_ready,
						    new_state->fence,
						    I915_FENCE_TIMEOUT,
						    GFP_KERNEL);
		if (ret < 0)
			return ret;
	}

	if (!obj)
		return 0;

	ret = i915_gem_object_pin_pages(obj);
	if (ret)
		return ret;

	ret = mutex_lock_interruptible(&dev_priv->drm.struct_mutex);
	if (ret) {
		i915_gem_object_unpin_pages(obj);
		return ret;
	}

	ret = intel_plane_pin_fb(to_intel_plane_state(new_state));

	mutex_unlock(&dev_priv->drm.struct_mutex);
	i915_gem_object_unpin_pages(obj);
	if (ret)
		return ret;

	fb_obj_bump_render_priority(obj);
	intel_frontbuffer_flush(obj->frontbuffer, ORIGIN_DIRTYFB);

	if (!new_state->fence) { /* implicit fencing */
		struct dma_fence *fence;

		ret = i915_sw_fence_await_reservation(&intel_state->commit_ready,
						      obj->base.resv, NULL,
						      false, I915_FENCE_TIMEOUT,
						      GFP_KERNEL);
		if (ret < 0)
			return ret;

		fence = dma_resv_get_excl_rcu(obj->base.resv);
		if (fence) {
			add_rps_boost_after_vblank(new_state->crtc, fence);
			dma_fence_put(fence);
		}
	} else {
		add_rps_boost_after_vblank(new_state->crtc, new_state->fence);
	}

	/*
	 * We declare pageflips to be interactive and so merit a small bias
	 * towards upclocking to deliver the frame on time. By only changing
	 * the RPS thresholds to sample more regularly and aim for higher
	 * clocks we can hopefully deliver low power workloads (like kodi)
	 * that are not quite steady state without resorting to forcing
	 * maximum clocks following a vblank miss (see do_rps_boost()).
	 */
	if (!intel_state->rps_interactive) {
		intel_rps_mark_interactive(dev_priv, true);
		intel_state->rps_interactive = true;
	}

	return 0;
}