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
struct pci_dev {scalar_t__ msi_enabled; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  pm_qos; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_perf_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_driver_hw_remove(struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;

	i915_perf_fini(dev_priv);

	if (pdev->msi_enabled)
		pci_disable_msi(pdev);

	pm_qos_remove_request(&dev_priv->pm_qos);
}