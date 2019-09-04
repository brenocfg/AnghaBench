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
 int /*<<< orphan*/  gma_resume_display (struct pci_dev*) ; 
 int /*<<< orphan*/  gma_resume_pci (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  power_mutex ; 
 int /*<<< orphan*/  psb_irq_postinstall (struct drm_device*) ; 
 int /*<<< orphan*/  psb_irq_preinstall (struct drm_device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

int gma_power_resume(struct device *_dev)
{
	struct pci_dev *pdev = to_pci_dev(_dev);
	struct drm_device *dev = pci_get_drvdata(pdev);

	mutex_lock(&power_mutex);
	gma_resume_pci(pdev);
	gma_resume_display(pdev);
	psb_irq_preinstall(dev);
	psb_irq_postinstall(dev);
	mutex_unlock(&power_mutex);
	return 0;
}