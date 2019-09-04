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
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int radeon_suspend_kms (struct drm_device*,int,int,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int radeon_pmops_freeze(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct drm_device *drm_dev = pci_get_drvdata(pdev);
	return radeon_suspend_kms(drm_dev, false, true, true);
}