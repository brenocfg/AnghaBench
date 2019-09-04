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
struct TYPE_2__ {int /*<<< orphan*/  hw_ida; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 unsigned int GEN11_MAX_CONTEXT_HW_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 unsigned int MAX_CONTEXT_HW_ID ; 
 unsigned int MAX_GUC_CONTEXT_HW_ID ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assign_hw_id(struct drm_i915_private *dev_priv, unsigned *out)
{
	int ret;
	unsigned int max;

	if (INTEL_GEN(dev_priv) >= 11) {
		max = GEN11_MAX_CONTEXT_HW_ID;
	} else {
		/*
		 * When using GuC in proxy submission, GuC consumes the
		 * highest bit in the context id to indicate proxy submission.
		 */
		if (USES_GUC_SUBMISSION(dev_priv))
			max = MAX_GUC_CONTEXT_HW_ID;
		else
			max = MAX_CONTEXT_HW_ID;
	}


	ret = ida_simple_get(&dev_priv->contexts.hw_ida,
			     0, max, GFP_KERNEL);
	if (ret < 0) {
		/* Contexts are only released when no longer active.
		 * Flush any pending retires to hopefully release some
		 * stale contexts and try again.
		 */
		i915_retire_requests(dev_priv);
		ret = ida_simple_get(&dev_priv->contexts.hw_ida,
				     0, max, GFP_KERNEL);
		if (ret < 0)
			return ret;
	}

	*out = ret;
	return 0;
}