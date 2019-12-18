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
struct pci_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct pci_dev {struct device dev; } ;
struct mii_bus {int /*<<< orphan*/  id; struct enetc_mdio_priv* priv; struct device* parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct enetc_mdio_priv {struct enetc_hw* hw; } ;
struct enetc_hw {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_MDIO_BUS_NAME ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 char* dev_name (struct device*) ; 
 struct enetc_hw* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc_size (struct device*,int) ; 
 int /*<<< orphan*/  enetc_mdio_read ; 
 int /*<<< orphan*/  enetc_mdio_write ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mii_bus*) ; 
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int enetc_pci_mdio_probe(struct pci_dev *pdev,
				const struct pci_device_id *ent)
{
	struct enetc_mdio_priv *mdio_priv;
	struct device *dev = &pdev->dev;
	struct enetc_hw *hw;
	struct mii_bus *bus;
	int err;

	hw = devm_kzalloc(dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	bus = devm_mdiobus_alloc_size(dev, sizeof(*mdio_priv));
	if (!bus)
		return -ENOMEM;

	bus->name = ENETC_MDIO_BUS_NAME;
	bus->read = enetc_mdio_read;
	bus->write = enetc_mdio_write;
	bus->parent = dev;
	mdio_priv = bus->priv;
	mdio_priv->hw = hw;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	pcie_flr(pdev);
	err = pci_enable_device_mem(pdev);
	if (err) {
		dev_err(dev, "device enable failed\n");
		return err;
	}

	err = pci_request_region(pdev, 0, KBUILD_MODNAME);
	if (err) {
		dev_err(dev, "pci_request_region failed\n");
		goto err_pci_mem_reg;
	}

	hw->port = pci_iomap(pdev, 0, 0);
	if (!hw->port) {
		err = -ENXIO;
		dev_err(dev, "iomap failed\n");
		goto err_ioremap;
	}

	err = of_mdiobus_register(bus, dev->of_node);
	if (err)
		goto err_mdiobus_reg;

	pci_set_drvdata(pdev, bus);

	return 0;

err_mdiobus_reg:
	iounmap(mdio_priv->hw->port);
err_ioremap:
	pci_release_mem_regions(pdev);
err_pci_mem_reg:
	pci_disable_device(pdev);

	return err;
}