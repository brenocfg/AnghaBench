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
 scalar_t__ DRM_SWITCH_POWER_DYNAMIC_OFF ; 
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int nouveau_do_suspend (struct drm_device*,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
nouveau_pmops_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct drm_device *drm_dev = pci_get_drvdata(pdev);
	int ret;

	if (drm_dev->switch_power_state == DRM_SWITCH_POWER_OFF ||
	    drm_dev->switch_power_state == DRM_SWITCH_POWER_DYNAMIC_OFF)
		return 0;

	ret = nouveau_do_suspend(drm_dev, false);
	if (ret)
		return ret;

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, PCI_D3hot);
	udelay(200);
	return 0;
}