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
 int /*<<< orphan*/  DC_STATE_EN ; 
 int DC_STATE_EN_UPTO_DC5 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int intel_irqs_enabled (struct drm_i915_private*) ; 

__attribute__((used)) static void assert_can_disable_dc9(struct drm_i915_private *dev_priv)
{
	WARN_ONCE(intel_irqs_enabled(dev_priv),
		  "Interrupts not disabled yet.\n");
	WARN_ONCE(I915_READ(DC_STATE_EN) & DC_STATE_EN_UPTO_DC5,
		  "DC5 still not disabled.\n");

	 /*
	  * TODO: check for the following to verify DC9 state was indeed
	  * entered before programming to disable it:
	  * 1] Check relevant display engine registers to verify if mode
	  *  set disable sequence was followed.
	  * 2] Check if display uninitialize sequence is initialized.
	  */
}