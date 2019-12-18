#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct mii_bus {char* name; int phy_mask; int /*<<< orphan*/ * parent; struct hclge_dev* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct hclge_mac {scalar_t__ phy_addr; struct mii_bus* mdio_bus; struct phy_device* phydev; } ;
struct TYPE_3__ {struct hclge_mac mac; } ;
struct hclge_dev {TYPE_2__* pdev; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ PHY_INEXISTENT ; 
 scalar_t__ PHY_MAX_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct mii_bus* devm_mdiobus_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_mdio_read ; 
 int /*<<< orphan*/  hclge_mdio_write ; 
 struct phy_device* mdiobus_get_phy (struct mii_bus*,int) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 

int hclge_mac_mdio_config(struct hclge_dev *hdev)
{
#define PHY_INEXISTENT	255

	struct hclge_mac *mac = &hdev->hw.mac;
	struct phy_device *phydev;
	struct mii_bus *mdio_bus;
	int ret;

	if (hdev->hw.mac.phy_addr == PHY_INEXISTENT) {
		dev_info(&hdev->pdev->dev,
			 "no phy device is connected to mdio bus\n");
		return 0;
	} else if (hdev->hw.mac.phy_addr >= PHY_MAX_ADDR) {
		dev_err(&hdev->pdev->dev, "phy_addr(%d) is too large.\n",
			hdev->hw.mac.phy_addr);
		return -EINVAL;
	}

	mdio_bus = devm_mdiobus_alloc(&hdev->pdev->dev);
	if (!mdio_bus)
		return -ENOMEM;

	mdio_bus->name = "hisilicon MII bus";
	mdio_bus->read = hclge_mdio_read;
	mdio_bus->write = hclge_mdio_write;
	snprintf(mdio_bus->id, MII_BUS_ID_SIZE, "%s-%s", "mii",
		 dev_name(&hdev->pdev->dev));

	mdio_bus->parent = &hdev->pdev->dev;
	mdio_bus->priv = hdev;
	mdio_bus->phy_mask = ~(1 << mac->phy_addr);
	ret = mdiobus_register(mdio_bus);
	if (ret) {
		dev_err(mdio_bus->parent,
			"Failed to register MDIO bus ret = %#x\n", ret);
		return ret;
	}

	phydev = mdiobus_get_phy(mdio_bus, mac->phy_addr);
	if (!phydev) {
		dev_err(mdio_bus->parent, "Failed to get phy device\n");
		mdiobus_unregister(mdio_bus);
		return -EIO;
	}

	mac->phydev = phydev;
	mac->mdio_bus = mdio_bus;

	return 0;
}