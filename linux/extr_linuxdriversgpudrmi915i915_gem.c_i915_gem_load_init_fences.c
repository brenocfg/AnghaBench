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
struct TYPE_3__ {int /*<<< orphan*/  fence_list; } ;
struct drm_i915_private {int num_fence_regs; TYPE_1__ mm; struct drm_i915_fence_reg* fence_regs; } ;
struct drm_i915_fence_reg {int id; int /*<<< orphan*/  link; struct drm_i915_private* i915; } ;
struct TYPE_4__ {int /*<<< orphan*/  fence_num; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G33 (struct drm_i915_private*) ; 
 scalar_t__ IS_I945G (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 TYPE_2__ avail_rs ; 
 int /*<<< orphan*/  i915_gem_detect_bit_6_swizzle (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgtif_reg (int /*<<< orphan*/ ) ; 

void
i915_gem_load_init_fences(struct drm_i915_private *dev_priv)
{
	int i;

	if (INTEL_GEN(dev_priv) >= 7 && !IS_VALLEYVIEW(dev_priv) &&
	    !IS_CHERRYVIEW(dev_priv))
		dev_priv->num_fence_regs = 32;
	else if (INTEL_GEN(dev_priv) >= 4 ||
		 IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
		 IS_G33(dev_priv) || IS_PINEVIEW(dev_priv))
		dev_priv->num_fence_regs = 16;
	else
		dev_priv->num_fence_regs = 8;

	if (intel_vgpu_active(dev_priv))
		dev_priv->num_fence_regs =
				I915_READ(vgtif_reg(avail_rs.fence_num));

	/* Initialize fence registers to zero */
	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct drm_i915_fence_reg *fence = &dev_priv->fence_regs[i];

		fence->i915 = dev_priv;
		fence->id = i;
		list_add_tail(&fence->link, &dev_priv->mm.fence_list);
	}
	i915_gem_restore_fences(dev_priv);

	i915_gem_detect_bit_6_swizzle(dev_priv);
}