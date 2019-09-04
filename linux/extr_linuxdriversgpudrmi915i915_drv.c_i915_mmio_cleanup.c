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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  regs; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_teardown_mchbar (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_mmio_cleanup(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;

	intel_teardown_mchbar(dev_priv);
	pci_iounmap(pdev, dev_priv->regs);
}