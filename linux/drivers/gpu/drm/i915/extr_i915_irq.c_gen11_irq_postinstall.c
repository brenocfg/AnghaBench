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
typedef  int /*<<< orphan*/  u32 ;
struct intel_uncore {int /*<<< orphan*/  regs; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_DISPLAY_INT_CTL ; 
 int /*<<< orphan*/  GEN11_DISPLAY_IRQ_ENABLE ; 
 int /*<<< orphan*/  GEN11_GFX_MSTR_IRQ ; 
 int /*<<< orphan*/  GEN11_GU_MISC_ ; 
 int /*<<< orphan*/  GEN11_GU_MISC_GSE ; 
 int /*<<< orphan*/  GEN3_IRQ_INIT (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INTEL_PCH_TYPE (struct drm_i915_private*) ; 
 scalar_t__ PCH_ICP ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen11_gt_irq_postinstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen11_master_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_de_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icp_irq_postinstall (struct drm_i915_private*) ; 

__attribute__((used)) static void gen11_irq_postinstall(struct drm_i915_private *dev_priv)
{
	struct intel_uncore *uncore = &dev_priv->uncore;
	u32 gu_misc_masked = GEN11_GU_MISC_GSE;

	if (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		icp_irq_postinstall(dev_priv);

	gen11_gt_irq_postinstall(&dev_priv->gt);
	gen8_de_irq_postinstall(dev_priv);

	GEN3_IRQ_INIT(uncore, GEN11_GU_MISC_, ~gu_misc_masked, gu_misc_masked);

	I915_WRITE(GEN11_DISPLAY_INT_CTL, GEN11_DISPLAY_IRQ_ENABLE);

	gen11_master_intr_enable(uncore->regs);
	POSTING_READ(GEN11_GFX_MSTR_IRQ);
}