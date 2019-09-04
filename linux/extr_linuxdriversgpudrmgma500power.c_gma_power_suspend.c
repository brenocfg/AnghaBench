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
struct drm_psb_private {scalar_t__ display_count; int /*<<< orphan*/  suspended; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gma_suspend_display (struct drm_device*) ; 
 int /*<<< orphan*/  gma_suspend_pci (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  power_mutex ; 
 int /*<<< orphan*/  psb_irq_uninstall (struct drm_device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

int gma_power_suspend(struct device *_dev)
{
	struct pci_dev *pdev = to_pci_dev(_dev);
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct drm_psb_private *dev_priv = dev->dev_private;

	mutex_lock(&power_mutex);
	if (!dev_priv->suspended) {
		if (dev_priv->display_count) {
			mutex_unlock(&power_mutex);
			dev_err(dev->dev, "GPU hardware busy, cannot suspend\n");
			return -EBUSY;
		}
		psb_irq_uninstall(dev);
		gma_suspend_display(dev);
		gma_suspend_pci(pdev);
	}
	mutex_unlock(&power_mutex);
	return 0;
}