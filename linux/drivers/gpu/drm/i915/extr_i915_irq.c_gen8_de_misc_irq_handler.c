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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EDP_PSR_IIR ; 
 int GEN8_DE_EDP_PSR ; 
 int GEN8_DE_MISC_GSE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_opregion_asle_intr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_psr_irq_handler (struct drm_i915_private*,int) ; 

__attribute__((used)) static void
gen8_de_misc_irq_handler(struct drm_i915_private *dev_priv, u32 iir)
{
	bool found = false;

	if (iir & GEN8_DE_MISC_GSE) {
		intel_opregion_asle_intr(dev_priv);
		found = true;
	}

	if (iir & GEN8_DE_EDP_PSR) {
		u32 psr_iir = I915_READ(EDP_PSR_IIR);

		intel_psr_irq_handler(dev_priv, psr_iir);
		I915_WRITE(EDP_PSR_IIR, psr_iir);
		found = true;
	}

	if (!found)
		DRM_ERROR("Unexpected DE Misc interrupt\n");
}