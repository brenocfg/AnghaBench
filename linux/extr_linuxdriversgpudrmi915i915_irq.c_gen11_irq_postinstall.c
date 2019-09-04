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
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_DISPLAY_INT_CTL ; 
 int /*<<< orphan*/  GEN11_DISPLAY_IRQ_ENABLE ; 
 int /*<<< orphan*/  GEN11_GFX_MSTR_IRQ ; 
 int /*<<< orphan*/  GEN11_GU_MISC_ ; 
 int /*<<< orphan*/  GEN11_GU_MISC_GSE ; 
 int /*<<< orphan*/  GEN11_MASTER_IRQ ; 
 int /*<<< orphan*/  GEN3_IRQ_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_ICP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen11_gt_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_de_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icp_irq_postinstall (struct drm_device*) ; 

__attribute__((used)) static int gen11_irq_postinstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 gu_misc_masked = GEN11_GU_MISC_GSE;

	if (HAS_PCH_ICP(dev_priv))
		icp_irq_postinstall(dev);

	gen11_gt_irq_postinstall(dev_priv);
	gen8_de_irq_postinstall(dev_priv);

	GEN3_IRQ_INIT(GEN11_GU_MISC_, ~gu_misc_masked, gu_misc_masked);

	I915_WRITE(GEN11_DISPLAY_INT_CTL, GEN11_DISPLAY_IRQ_ENABLE);

	I915_WRITE(GEN11_GFX_MSTR_IRQ, GEN11_MASTER_IRQ);
	POSTING_READ(GEN11_GFX_MSTR_IRQ);

	return 0;
}