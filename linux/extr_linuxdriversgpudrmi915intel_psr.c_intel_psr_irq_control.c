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
struct TYPE_2__ {int /*<<< orphan*/  debug; } ;
struct drm_i915_private {TYPE_1__ psr; } ;

/* Variables and functions */
 int EDP_PSR_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDP_PSR_IMR ; 
 int EDP_PSR_POST_EXIT (int /*<<< orphan*/ ) ; 
 int EDP_PSR_PRE_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  TRANSCODER_A ; 
 int /*<<< orphan*/  TRANSCODER_B ; 
 int /*<<< orphan*/  TRANSCODER_C ; 
 int /*<<< orphan*/  TRANSCODER_EDP ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 

void intel_psr_irq_control(struct drm_i915_private *dev_priv, bool debug)
{
	u32 debug_mask, mask;

	mask = EDP_PSR_ERROR(TRANSCODER_EDP);
	debug_mask = EDP_PSR_POST_EXIT(TRANSCODER_EDP) |
		     EDP_PSR_PRE_ENTRY(TRANSCODER_EDP);

	if (INTEL_GEN(dev_priv) >= 8) {
		mask |= EDP_PSR_ERROR(TRANSCODER_A) |
			EDP_PSR_ERROR(TRANSCODER_B) |
			EDP_PSR_ERROR(TRANSCODER_C);

		debug_mask |= EDP_PSR_POST_EXIT(TRANSCODER_A) |
			      EDP_PSR_PRE_ENTRY(TRANSCODER_A) |
			      EDP_PSR_POST_EXIT(TRANSCODER_B) |
			      EDP_PSR_PRE_ENTRY(TRANSCODER_B) |
			      EDP_PSR_POST_EXIT(TRANSCODER_C) |
			      EDP_PSR_PRE_ENTRY(TRANSCODER_C);
	}

	if (debug)
		mask |= debug_mask;

	WRITE_ONCE(dev_priv->psr.debug, debug);
	I915_WRITE(EDP_PSR_IMR, ~mask);
}