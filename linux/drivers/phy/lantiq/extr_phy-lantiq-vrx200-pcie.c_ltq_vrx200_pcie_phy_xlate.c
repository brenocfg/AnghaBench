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
struct of_phandle_args {int args_count; unsigned int* args; } ;
struct ltq_vrx200_pcie_phy_priv {unsigned int mode; struct phy* phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  LANTIQ_PCIE_PHY_MODE_100MHZ 133 
#define  LANTIQ_PCIE_PHY_MODE_100MHZ_SSC 132 
#define  LANTIQ_PCIE_PHY_MODE_25MHZ 131 
#define  LANTIQ_PCIE_PHY_MODE_25MHZ_SSC 130 
#define  LANTIQ_PCIE_PHY_MODE_36MHZ 129 
#define  LANTIQ_PCIE_PHY_MODE_36MHZ_SSC 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ltq_vrx200_pcie_phy_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *ltq_vrx200_pcie_phy_xlate(struct device *dev,
					     struct of_phandle_args *args)
{
	struct ltq_vrx200_pcie_phy_priv *priv = dev_get_drvdata(dev);
	unsigned int mode;

	if (args->args_count != 1) {
		dev_err(dev, "invalid number of arguments\n");
		return ERR_PTR(-EINVAL);
	}

	mode = args->args[0];

	switch (mode) {
	case LANTIQ_PCIE_PHY_MODE_36MHZ:
		priv->mode = mode;
		break;

	case LANTIQ_PCIE_PHY_MODE_25MHZ:
	case LANTIQ_PCIE_PHY_MODE_25MHZ_SSC:
	case LANTIQ_PCIE_PHY_MODE_36MHZ_SSC:
	case LANTIQ_PCIE_PHY_MODE_100MHZ:
	case LANTIQ_PCIE_PHY_MODE_100MHZ_SSC:
		dev_err(dev, "PHY mode not implemented yet: %u\n", mode);
		return ERR_PTR(-EINVAL);

	default:
		dev_err(dev, "invalid PHY mode %u\n", mode);
		return ERR_PTR(-EINVAL);
	};

	return priv->phy;
}