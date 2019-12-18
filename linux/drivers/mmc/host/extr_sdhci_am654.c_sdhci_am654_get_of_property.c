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
struct sdhci_am654_data {int otap_del_sel; int flags; int trm_icp; int strb_sel; int /*<<< orphan*/  drv_strength; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int DLL_PRESENT ; 
 int /*<<< orphan*/  DRIVER_STRENGTH_100_OHM ; 
 int /*<<< orphan*/  DRIVER_STRENGTH_33_OHM ; 
 int /*<<< orphan*/  DRIVER_STRENGTH_40_OHM ; 
 int /*<<< orphan*/  DRIVER_STRENGTH_50_OHM ; 
 int /*<<< orphan*/  DRIVER_STRENGTH_66_OHM ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 

__attribute__((used)) static int sdhci_am654_get_of_property(struct platform_device *pdev,
					struct sdhci_am654_data *sdhci_am654)
{
	struct device *dev = &pdev->dev;
	int drv_strength;
	int ret;

	ret = device_property_read_u32(dev, "ti,otap-del-sel",
				       &sdhci_am654->otap_del_sel);
	if (ret)
		return ret;

	if (sdhci_am654->flags & DLL_PRESENT) {
		ret = device_property_read_u32(dev, "ti,trm-icp",
					       &sdhci_am654->trm_icp);
		if (ret)
			return ret;

		ret = device_property_read_u32(dev, "ti,driver-strength-ohm",
					       &drv_strength);
		if (ret)
			return ret;

		switch (drv_strength) {
		case 50:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_50_OHM;
			break;
		case 33:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_33_OHM;
			break;
		case 66:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_66_OHM;
			break;
		case 100:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_100_OHM;
			break;
		case 40:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_40_OHM;
			break;
		default:
			dev_err(dev, "Invalid driver strength\n");
			return -EINVAL;
		}
	}

	device_property_read_u32(dev, "ti,strobe-sel", &sdhci_am654->strb_sel);

	sdhci_get_of_property(pdev);

	return 0;
}