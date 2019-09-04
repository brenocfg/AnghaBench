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
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  EMR ; 
 int I915_MASTER_ERROR_INTERRUPT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IIR ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IPEIR ; 
 int /*<<< orphan*/  IPEIR_I965 ; 
 int /*<<< orphan*/  IS_GEN2 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PGTBL_ER ; 

__attribute__((used)) static void i915_clear_error_registers(struct drm_i915_private *dev_priv)
{
	u32 eir;

	if (!IS_GEN2(dev_priv))
		I915_WRITE(PGTBL_ER, I915_READ(PGTBL_ER));

	if (INTEL_GEN(dev_priv) < 4)
		I915_WRITE(IPEIR, I915_READ(IPEIR));
	else
		I915_WRITE(IPEIR_I965, I915_READ(IPEIR_I965));

	I915_WRITE(EIR, I915_READ(EIR));
	eir = I915_READ(EIR);
	if (eir) {
		/*
		 * some errors might have become stuck,
		 * mask them.
		 */
		DRM_DEBUG_DRIVER("EIR stuck: 0x%08x, masking\n", eir);
		I915_WRITE(EMR, I915_READ(EMR) | eir);
		I915_WRITE(IIR, I915_MASTER_ERROR_INTERRUPT);
	}
}