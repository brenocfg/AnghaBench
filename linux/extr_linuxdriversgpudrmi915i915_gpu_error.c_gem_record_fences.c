#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_gpu_state {int nfence; void** fence; struct drm_i915_private* i915; } ;
struct drm_i915_private {int num_fence_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FENCE_REG (int) ; 
 int /*<<< orphan*/  FENCE_REG_965_LO (int) ; 
 int /*<<< orphan*/  FENCE_REG_GEN6_LO (int) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 void* I915_READ64 (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static void gem_record_fences(struct i915_gpu_state *error)
{
	struct drm_i915_private *dev_priv = error->i915;
	int i;

	if (INTEL_GEN(dev_priv) >= 6) {
		for (i = 0; i < dev_priv->num_fence_regs; i++)
			error->fence[i] = I915_READ64(FENCE_REG_GEN6_LO(i));
	} else if (INTEL_GEN(dev_priv) >= 4) {
		for (i = 0; i < dev_priv->num_fence_regs; i++)
			error->fence[i] = I915_READ64(FENCE_REG_965_LO(i));
	} else {
		for (i = 0; i < dev_priv->num_fence_regs; i++)
			error->fence[i] = I915_READ(FENCE_REG(i));
	}
	error->nfence = i;
}