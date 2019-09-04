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
struct drm_psb_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hotplug_work; } ;
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_hotplug_enable (struct drm_device*,int) ; 
 int /*<<< orphan*/  cdv_hotplug_work_func ; 
 int /*<<< orphan*/  cdv_regmap ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gma_get_core_freq (struct drm_device*) ; 
 scalar_t__ pci_enable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_init_bios (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_opregion_init (struct drm_device*) ; 

__attribute__((used)) static int cdv_chip_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	INIT_WORK(&dev_priv->hotplug_work, cdv_hotplug_work_func);

	if (pci_enable_msi(dev->pdev))
		dev_warn(dev->dev, "Enabling MSI failed!\n");
	dev_priv->regmap = cdv_regmap;
	gma_get_core_freq(dev);
	psb_intel_opregion_init(dev);
	psb_intel_init_bios(dev);
	cdv_hotplug_enable(dev, false);
	return 0;
}