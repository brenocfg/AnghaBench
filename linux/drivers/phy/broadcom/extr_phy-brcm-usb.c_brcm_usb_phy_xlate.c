#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy {int dummy; } ;
struct of_phandle_args {int* args; } ;
struct device {int dummy; } ;
struct brcm_usb_phy_data {TYPE_1__* phys; } ;
struct TYPE_2__ {struct phy* phy; } ;

/* Variables and functions */
 size_t BRCM_USB_PHY_2_0 ; 
 size_t BRCM_USB_PHY_3_0 ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  PHY_TYPE_USB2 129 
#define  PHY_TYPE_USB3 128 
 struct brcm_usb_phy_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static struct phy *brcm_usb_phy_xlate(struct device *dev,
				      struct of_phandle_args *args)
{
	struct brcm_usb_phy_data *data = dev_get_drvdata(dev);

	/*
	 * values 0 and 1 are for backward compatibility with
	 * device tree nodes from older bootloaders.
	 */
	switch (args->args[0]) {
	case 0:
	case PHY_TYPE_USB2:
		if (data->phys[BRCM_USB_PHY_2_0].phy)
			return data->phys[BRCM_USB_PHY_2_0].phy;
		dev_warn(dev, "Error, 2.0 Phy not found\n");
		break;
	case 1:
	case PHY_TYPE_USB3:
		if (data->phys[BRCM_USB_PHY_3_0].phy)
			return data->phys[BRCM_USB_PHY_3_0].phy;
		dev_warn(dev, "Error, 3.0 Phy not found\n");
		break;
	}
	return ERR_PTR(-ENODEV);
}