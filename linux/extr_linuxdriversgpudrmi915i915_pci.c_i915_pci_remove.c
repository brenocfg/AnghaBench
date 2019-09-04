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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  i915_driver_unload (struct drm_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_pci_remove(struct pci_dev *pdev)
{
	struct drm_device *dev;

	dev = pci_get_drvdata(pdev);
	if (!dev) /* driver load aborted, nothing to cleanup */
		return;

	i915_driver_unload(dev);
	drm_dev_put(dev);

	pci_set_drvdata(pdev, NULL);
}