#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int en; } ;
union cvmx_smix_en {scalar_t__ u64; TYPE_1__ s; } ;
typedef  scalar_t__ u64 ;
struct resource {int /*<<< orphan*/  name; int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mii_bus {int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_2__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/  name; struct cavium_mdiobus* priv; } ;
struct cavium_mdiobus {scalar_t__ register_base; struct mii_bus* mii_bus; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ SMI_EN ; 
 int /*<<< orphan*/  cavium_mdiobus_read ; 
 int /*<<< orphan*/  cavium_mdiobus_write ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 scalar_t__ devm_ioremap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc_size (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  oct_mdio_writeq (scalar_t__,scalar_t__) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cavium_mdiobus*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int octeon_mdiobus_probe(struct platform_device *pdev)
{
	struct cavium_mdiobus *bus;
	struct mii_bus *mii_bus;
	struct resource *res_mem;
	resource_size_t mdio_phys;
	resource_size_t regsize;
	union cvmx_smix_en smi_en;
	int err = -ENOENT;

	mii_bus = devm_mdiobus_alloc_size(&pdev->dev, sizeof(*bus));
	if (!mii_bus)
		return -ENOMEM;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res_mem == NULL) {
		dev_err(&pdev->dev, "found no memory resource\n");
		return -ENXIO;
	}

	bus = mii_bus->priv;
	bus->mii_bus = mii_bus;
	mdio_phys = res_mem->start;
	regsize = resource_size(res_mem);

	if (!devm_request_mem_region(&pdev->dev, mdio_phys, regsize,
				     res_mem->name)) {
		dev_err(&pdev->dev, "request_mem_region failed\n");
		return -ENXIO;
	}

	bus->register_base =
		(u64)devm_ioremap(&pdev->dev, mdio_phys, regsize);
	if (!bus->register_base) {
		dev_err(&pdev->dev, "dev_ioremap failed\n");
		return -ENOMEM;
	}

	smi_en.u64 = 0;
	smi_en.s.en = 1;
	oct_mdio_writeq(smi_en.u64, bus->register_base + SMI_EN);

	bus->mii_bus->name = KBUILD_MODNAME;
	snprintf(bus->mii_bus->id, MII_BUS_ID_SIZE, "%llx", bus->register_base);
	bus->mii_bus->parent = &pdev->dev;

	bus->mii_bus->read = cavium_mdiobus_read;
	bus->mii_bus->write = cavium_mdiobus_write;

	platform_set_drvdata(pdev, bus);

	err = of_mdiobus_register(bus->mii_bus, pdev->dev.of_node);
	if (err)
		goto fail_register;

	dev_info(&pdev->dev, "Probed\n");

	return 0;
fail_register:
	mdiobus_free(bus->mii_bus);
	smi_en.u64 = 0;
	oct_mdio_writeq(smi_en.u64, bus->register_base + SMI_EN);
	return err;
}