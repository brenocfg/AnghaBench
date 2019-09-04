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
struct drm_device {scalar_t__ switch_power_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i915_drm_prepare (struct drm_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int i915_pm_prepare(struct device *kdev)
{
	struct pci_dev *pdev = to_pci_dev(kdev);
	struct drm_device *dev = pci_get_drvdata(pdev);

	if (!dev) {
		dev_err(kdev, "DRM not initialized, aborting suspend.\n");
		return -ENODEV;
	}

	if (dev->switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	return i915_drm_prepare(dev);
}