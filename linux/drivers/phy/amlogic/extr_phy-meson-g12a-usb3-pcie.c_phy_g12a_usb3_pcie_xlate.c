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
struct phy_g12a_usb3_pcie_priv {unsigned int mode; struct phy* phy; } ;
struct phy {int dummy; } ;
struct of_phandle_args {int args_count; unsigned int* args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int PHY_TYPE_PCIE ; 
 unsigned int PHY_TYPE_USB3 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct phy_g12a_usb3_pcie_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *phy_g12a_usb3_pcie_xlate(struct device *dev,
					    struct of_phandle_args *args)
{
	struct phy_g12a_usb3_pcie_priv *priv = dev_get_drvdata(dev);
	unsigned int mode;

	if (args->args_count < 1) {
		dev_err(dev, "invalid number of arguments\n");
		return ERR_PTR(-EINVAL);
	}

	mode = args->args[0];

	if (mode != PHY_TYPE_USB3 && mode != PHY_TYPE_PCIE) {
		dev_err(dev, "invalid phy mode select argument\n");
		return ERR_PTR(-EINVAL);
	}

	priv->mode = mode;

	return priv->phy;
}