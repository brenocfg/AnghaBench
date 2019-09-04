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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE ; 
 int /*<<< orphan*/  EDP_PSR_IIR ; 
 int /*<<< orphan*/  EDP_PSR_IMR ; 
 int /*<<< orphan*/  GEN3_IRQ_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 int /*<<< orphan*/  HWSTAM ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen5_gt_irq_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ibx_irq_reset (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void ironlake_irq_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (IS_GEN5(dev_priv))
		I915_WRITE(HWSTAM, 0xffffffff);

	GEN3_IRQ_RESET(DE);
	if (IS_GEN7(dev_priv))
		I915_WRITE(GEN7_ERR_INT, 0xffffffff);

	if (IS_HASWELL(dev_priv)) {
		I915_WRITE(EDP_PSR_IMR, 0xffffffff);
		I915_WRITE(EDP_PSR_IIR, 0xffffffff);
	}

	gen5_gt_irq_reset(dev_priv);

	ibx_irq_reset(dev_priv);
}