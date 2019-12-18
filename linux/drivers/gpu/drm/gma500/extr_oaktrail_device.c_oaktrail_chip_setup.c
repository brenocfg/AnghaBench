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
struct drm_psb_private {int /*<<< orphan*/  has_gct; int /*<<< orphan*/  regmap; } ;
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gma_intel_setup_gmbus (struct drm_device*) ; 
 int mid_chip_setup (struct drm_device*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_setup (struct drm_device*) ; 
 int /*<<< orphan*/  oaktrail_regmap ; 
 scalar_t__ pci_enable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_init_bios (struct drm_device*) ; 
 int /*<<< orphan*/  psb_intel_opregion_init (struct drm_device*) ; 

__attribute__((used)) static int oaktrail_chip_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	int ret;
	
	if (pci_enable_msi(dev->pdev))
		dev_warn(dev->dev, "Enabling MSI failed!\n");

	dev_priv->regmap = oaktrail_regmap;

	ret = mid_chip_setup(dev);
	if (ret < 0)
		return ret;
	if (!dev_priv->has_gct) {
		/* Now pull the BIOS data */
		psb_intel_opregion_init(dev);
		psb_intel_init_bios(dev);
	}
	gma_intel_setup_gmbus(dev);
	oaktrail_hdmi_setup(dev);
	return 0;
}