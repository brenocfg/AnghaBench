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
struct drm_psb_private {int /*<<< orphan*/  regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdfld_regmap ; 
 int mid_chip_setup (struct drm_device*) ; 
 scalar_t__ pci_enable_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdfld_chip_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	if (pci_enable_msi(dev->pdev))
		dev_warn(dev->dev, "Enabling MSI failed!\n");
	dev_priv->regmap = mdfld_regmap;
	return mid_chip_setup(dev);
}