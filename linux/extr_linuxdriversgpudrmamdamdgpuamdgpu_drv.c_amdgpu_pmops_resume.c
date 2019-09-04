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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ amdgpu_device_is_px (struct drm_device*) ; 
 int amdgpu_device_resume (struct drm_device*,int,int) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int amdgpu_pmops_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct drm_device *drm_dev = pci_get_drvdata(pdev);

	/* GPU comes up enabled by the bios on resume */
	if (amdgpu_device_is_px(drm_dev)) {
		pm_runtime_disable(dev);
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	return amdgpu_device_resume(drm_dev, true, true);
}