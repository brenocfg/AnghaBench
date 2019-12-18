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
struct drm_i915_private {int /*<<< orphan*/  gt; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE ; 
 int /*<<< orphan*/  EDP_PSR_IIR ; 
 int /*<<< orphan*/  EDP_PSR_IMR ; 
 int /*<<< orphan*/  GEN3_IRQ_RESET (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen5_gt_irq_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibx_irq_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ironlake_irq_reset(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;

	GEN3_IRQ_RESET(uncore, DE);
	if (IS_GEN(dev_priv, 7))
		intel_uncore_write(uncore, GEN7_ERR_INT, 0xffffffff);

	if (IS_HASWELL(dev_priv)) {
		intel_uncore_write(uncore, EDP_PSR_IMR, 0xffffffff);
		intel_uncore_write(uncore, EDP_PSR_IIR, 0xffffffff);
	}

	gen5_gt_irq_reset(&dev_priv->gt);

	ibx_irq_reset(dev_priv);
}