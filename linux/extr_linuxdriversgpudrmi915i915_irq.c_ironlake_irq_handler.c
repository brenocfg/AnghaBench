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
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEIER ; 
 int /*<<< orphan*/  DEIIR ; 
 int DE_MASTER_IRQ_CONTROL ; 
 int /*<<< orphan*/  GEN6_PMIIR ; 
 int /*<<< orphan*/  GTIIR ; 
 int /*<<< orphan*/  HAS_PCH_NOP (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SDEIER ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_rps_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ilk_display_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  ilk_gt_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_irqs_enabled (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ivb_display_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  snb_gt_irq_handler (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static irqreturn_t ironlake_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u32 de_iir, gt_iir, de_ier, sde_ier = 0;
	irqreturn_t ret = IRQ_NONE;

	if (!intel_irqs_enabled(dev_priv))
		return IRQ_NONE;

	/* IRQs are synced during runtime_suspend, we don't require a wakeref */
	disable_rpm_wakeref_asserts(dev_priv);

	/* disable master interrupt before clearing iir  */
	de_ier = I915_READ(DEIER);
	I915_WRITE(DEIER, de_ier & ~DE_MASTER_IRQ_CONTROL);

	/* Disable south interrupts. We'll only write to SDEIIR once, so further
	 * interrupts will will be stored on its back queue, and then we'll be
	 * able to process them after we restore SDEIER (as soon as we restore
	 * it, we'll get an interrupt if SDEIIR still has something to process
	 * due to its back queue). */
	if (!HAS_PCH_NOP(dev_priv)) {
		sde_ier = I915_READ(SDEIER);
		I915_WRITE(SDEIER, 0);
	}

	/* Find, clear, then process each source of interrupt */

	gt_iir = I915_READ(GTIIR);
	if (gt_iir) {
		I915_WRITE(GTIIR, gt_iir);
		ret = IRQ_HANDLED;
		if (INTEL_GEN(dev_priv) >= 6)
			snb_gt_irq_handler(dev_priv, gt_iir);
		else
			ilk_gt_irq_handler(dev_priv, gt_iir);
	}

	de_iir = I915_READ(DEIIR);
	if (de_iir) {
		I915_WRITE(DEIIR, de_iir);
		ret = IRQ_HANDLED;
		if (INTEL_GEN(dev_priv) >= 7)
			ivb_display_irq_handler(dev_priv, de_iir);
		else
			ilk_display_irq_handler(dev_priv, de_iir);
	}

	if (INTEL_GEN(dev_priv) >= 6) {
		u32 pm_iir = I915_READ(GEN6_PMIIR);
		if (pm_iir) {
			I915_WRITE(GEN6_PMIIR, pm_iir);
			ret = IRQ_HANDLED;
			gen6_rps_irq_handler(dev_priv, pm_iir);
		}
	}

	I915_WRITE(DEIER, de_ier);
	if (!HAS_PCH_NOP(dev_priv))
		I915_WRITE(SDEIER, sde_ier);

	/* IRQs are synced during runtime_suspend, we don't require a wakeref */
	enable_rpm_wakeref_asserts(dev_priv);

	return ret;
}