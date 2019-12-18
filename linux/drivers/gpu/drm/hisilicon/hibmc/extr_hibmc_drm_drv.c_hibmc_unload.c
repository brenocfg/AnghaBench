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
struct hibmc_drm_private {scalar_t__ msi_enabled; } ;
struct drm_device {struct hibmc_drm_private* dev_private; int /*<<< orphan*/  pdev; scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  hibmc_fbdev_fini (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  hibmc_kms_fini (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  hibmc_mm_fini (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hibmc_unload(struct drm_device *dev)
{
	struct hibmc_drm_private *priv = dev->dev_private;

	hibmc_fbdev_fini(priv);

	drm_atomic_helper_shutdown(dev);

	if (dev->irq_enabled)
		drm_irq_uninstall(dev);
	if (priv->msi_enabled)
		pci_disable_msi(dev->pdev);

	hibmc_kms_fini(priv);
	hibmc_mm_fini(priv);
	dev->dev_private = NULL;
	return 0;
}