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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_LOGICAL_RING_CONTEXTS (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  USES_PPGTT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_ppgtt_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen7_ppgtt_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_ppgtt_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gtt_write_workarounds (struct drm_i915_private*) ; 

int i915_ppgtt_init_hw(struct drm_i915_private *dev_priv)
{
	gtt_write_workarounds(dev_priv);

	/* In the case of execlists, PPGTT is enabled by the context descriptor
	 * and the PDPs are contained within the context itself.  We don't
	 * need to do anything here. */
	if (HAS_LOGICAL_RING_CONTEXTS(dev_priv))
		return 0;

	if (!USES_PPGTT(dev_priv))
		return 0;

	if (IS_GEN6(dev_priv))
		gen6_ppgtt_enable(dev_priv);
	else if (IS_GEN7(dev_priv))
		gen7_ppgtt_enable(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 8)
		gen8_ppgtt_enable(dev_priv);
	else
		MISSING_CASE(INTEL_GEN(dev_priv));

	return 0;
}