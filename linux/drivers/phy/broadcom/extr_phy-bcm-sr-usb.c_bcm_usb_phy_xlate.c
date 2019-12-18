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
struct phy {int dummy; } ;
struct of_phandle_args {int* args; } ;
struct device {int dummy; } ;
struct bcm_usb_phy_cfg {scalar_t__ version; struct phy* phy; } ;

/* Variables and functions */
 scalar_t__ BCM_SR_USB_COMBO_PHY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct bcm_usb_phy_cfg* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *bcm_usb_phy_xlate(struct device *dev,
				     struct of_phandle_args *args)
{
	struct bcm_usb_phy_cfg *phy_cfg;
	int phy_idx;

	phy_cfg = dev_get_drvdata(dev);
	if (!phy_cfg)
		return ERR_PTR(-EINVAL);

	if (phy_cfg->version == BCM_SR_USB_COMBO_PHY) {
		phy_idx = args->args[0];

		if (WARN_ON(phy_idx > 1))
			return ERR_PTR(-ENODEV);

		return phy_cfg[phy_idx].phy;
	} else
		return phy_cfg->phy;
}