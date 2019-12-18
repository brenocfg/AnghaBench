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
struct intel_uncore {int dummy; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_IRQ_RESET (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_NOP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDE ; 
 int /*<<< orphan*/  SERR_INT ; 

__attribute__((used)) static void ibx_irq_reset(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;

	if (HAS_PCH_NOP(dev_priv))
		return;

	GEN3_IRQ_RESET(uncore, SDE);

	if (HAS_PCH_CPT(dev_priv) || HAS_PCH_LPT(dev_priv))
		I915_WRITE(SERR_INT, 0xffffffff);
}