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
typedef  int u32 ;
struct i915_vma {scalar_t__ fence; } ;
struct i915_ggtt_view {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_fb_pin; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_1__ gpu_error; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_framebuffer {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PIN_MAPPABLE ; 
 unsigned long PLANE_HAS_FENCE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 struct i915_vma* i915_gem_object_pin_to_display_plane (struct drm_i915_gem_object*,int,struct i915_ggtt_view const*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_from_display_plane (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_get (struct i915_vma*) ; 
 scalar_t__ i915_vma_is_map_and_fenceable (struct i915_vma*) ; 
 int i915_vma_pin_fence (struct i915_vma*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_scanout_needs_vtd_wa (struct drm_i915_private*) ; 
 int intel_surf_alignment (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

struct i915_vma *
intel_pin_and_fence_fb_obj(struct drm_framebuffer *fb,
			   const struct i915_ggtt_view *view,
			   bool uses_fence,
			   unsigned long *out_flags)
{
	struct drm_device *dev = fb->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_gem_object *obj = intel_fb_obj(fb);
	intel_wakeref_t wakeref;
	struct i915_vma *vma;
	unsigned int pinctl;
	u32 alignment;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	alignment = intel_surf_alignment(fb, 0);

	/* Note that the w/a also requires 64 PTE of padding following the
	 * bo. We currently fill all unused PTE with the shadow page and so
	 * we should always have valid PTE following the scanout preventing
	 * the VT-d warning.
	 */
	if (intel_scanout_needs_vtd_wa(dev_priv) && alignment < 256 * 1024)
		alignment = 256 * 1024;

	/*
	 * Global gtt pte registers are special registers which actually forward
	 * writes to a chunk of system memory. Which means that there is no risk
	 * that the register values disappear as soon as we call
	 * intel_runtime_pm_put(), so it is correct to wrap only the
	 * pin/unpin/fence and not more.
	 */
	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);
	i915_gem_object_lock(obj);

	atomic_inc(&dev_priv->gpu_error.pending_fb_pin);

	pinctl = 0;

	/* Valleyview is definitely limited to scanning out the first
	 * 512MiB. Lets presume this behaviour was inherited from the
	 * g4x display engine and that all earlier gen are similarly
	 * limited. Testing suggests that it is a little more
	 * complicated than this. For example, Cherryview appears quite
	 * happy to scanout from anywhere within its global aperture.
	 */
	if (HAS_GMCH(dev_priv))
		pinctl |= PIN_MAPPABLE;

	vma = i915_gem_object_pin_to_display_plane(obj,
						   alignment, view, pinctl);
	if (IS_ERR(vma))
		goto err;

	if (uses_fence && i915_vma_is_map_and_fenceable(vma)) {
		int ret;

		/* Install a fence for tiled scan-out. Pre-i965 always needs a
		 * fence, whereas 965+ only requires a fence if using
		 * framebuffer compression.  For simplicity, we always, when
		 * possible, install a fence as the cost is not that onerous.
		 *
		 * If we fail to fence the tiled scanout, then either the
		 * modeset will reject the change (which is highly unlikely as
		 * the affected systems, all but one, do not have unmappable
		 * space) or we will not be able to enable full powersaving
		 * techniques (also likely not to apply due to various limits
		 * FBC and the like impose on the size of the buffer, which
		 * presumably we violated anyway with this unmappable buffer).
		 * Anyway, it is presumably better to stumble onwards with
		 * something and try to run the system in a "less than optimal"
		 * mode that matches the user configuration.
		 */
		ret = i915_vma_pin_fence(vma);
		if (ret != 0 && INTEL_GEN(dev_priv) < 4) {
			i915_gem_object_unpin_from_display_plane(vma);
			vma = ERR_PTR(ret);
			goto err;
		}

		if (ret == 0 && vma->fence)
			*out_flags |= PLANE_HAS_FENCE;
	}

	i915_vma_get(vma);
err:
	atomic_dec(&dev_priv->gpu_error.pending_fb_pin);

	i915_gem_object_unlock(obj);
	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);
	return vma;
}