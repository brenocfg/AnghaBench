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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_sdvo {scalar_t__ port; int /*<<< orphan*/  sdvo_reg; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_SDVOB ; 
 int /*<<< orphan*/  GEN3_SDVOC ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PORT_B ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_sdvo_write_sdvox(struct intel_sdvo *intel_sdvo, u32 val)
{
	struct drm_device *dev = intel_sdvo->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 bval = val, cval = val;
	int i;

	if (HAS_PCH_SPLIT(dev_priv)) {
		I915_WRITE(intel_sdvo->sdvo_reg, val);
		POSTING_READ(intel_sdvo->sdvo_reg);
		/*
		 * HW workaround, need to write this twice for issue
		 * that may result in first write getting masked.
		 */
		if (HAS_PCH_IBX(dev_priv)) {
			I915_WRITE(intel_sdvo->sdvo_reg, val);
			POSTING_READ(intel_sdvo->sdvo_reg);
		}
		return;
	}

	if (intel_sdvo->port == PORT_B)
		cval = I915_READ(GEN3_SDVOC);
	else
		bval = I915_READ(GEN3_SDVOB);

	/*
	 * Write the registers twice for luck. Sometimes,
	 * writing them only once doesn't appear to 'stick'.
	 * The BIOS does this too. Yay, magic
	 */
	for (i = 0; i < 2; i++) {
		I915_WRITE(GEN3_SDVOB, bval);
		POSTING_READ(GEN3_SDVOB);

		I915_WRITE(GEN3_SDVOC, cval);
		POSTING_READ(GEN3_SDVOC);
	}
}