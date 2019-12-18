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
struct pci_dev {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_driver_remove (struct drm_i915_private*) ; 
 struct drm_i915_private* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_pci_remove(struct pci_dev *pdev)
{
	struct drm_i915_private *i915;

	i915 = pci_get_drvdata(pdev);
	if (!i915) /* driver load aborted, nothing to cleanup */
		return;

	i915_driver_remove(i915);
	pci_set_drvdata(pdev, NULL);

	drm_dev_put(&i915->drm);
}