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
typedef  int u32 ;
struct temac_local {int /*<<< orphan*/  dev; struct mii_bus* mii_bus; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct temac_local* priv; int /*<<< orphan*/  id; } ;
struct ll_temac_platform_data {int mdio_clk_freq; unsigned long long mdio_bus_id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  XTE_MC_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ll_temac_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct device_node* dev_of_node (int /*<<< orphan*/ *) ; 
 struct mii_bus* devm_mdiobus_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  temac_indirect_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  temac_mdio_read ; 
 int /*<<< orphan*/  temac_mdio_write ; 

int temac_mdio_setup(struct temac_local *lp, struct platform_device *pdev)
{
	struct ll_temac_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *np = dev_of_node(&pdev->dev);
	struct mii_bus *bus;
	u32 bus_hz;
	int clk_div;
	int rc;
	struct resource res;

	/* Get MDIO bus frequency (if specified) */
	bus_hz = 0;
	if (np)
		of_property_read_u32(np, "clock-frequency", &bus_hz);
	else if (pdata)
		bus_hz = pdata->mdio_clk_freq;

	/* Calculate a reasonable divisor for the clock rate */
	clk_div = 0x3f; /* worst-case default setting */
	if (bus_hz != 0) {
		clk_div = bus_hz / (2500 * 1000 * 2) - 1;
		if (clk_div < 1)
			clk_div = 1;
		if (clk_div > 0x3f)
			clk_div = 0x3f;
	}

	/* Enable the MDIO bus by asserting the enable bit and writing
	 * in the clock config */
	temac_indirect_out32(lp, XTE_MC_OFFSET, 1 << 6 | clk_div);

	bus = devm_mdiobus_alloc(&pdev->dev);
	if (!bus)
		return -ENOMEM;

	if (np) {
		of_address_to_resource(np, 0, &res);
		snprintf(bus->id, MII_BUS_ID_SIZE, "%.8llx",
			 (unsigned long long)res.start);
	} else if (pdata) {
		snprintf(bus->id, MII_BUS_ID_SIZE, "%.8llx",
			 pdata->mdio_bus_id);
	}

	bus->priv = lp;
	bus->name = "Xilinx TEMAC MDIO";
	bus->read = temac_mdio_read;
	bus->write = temac_mdio_write;
	bus->parent = lp->dev;

	lp->mii_bus = bus;

	rc = of_mdiobus_register(bus, np);
	if (rc)
		return rc;

	dev_dbg(lp->dev, "MDIO bus registered;  MC:%x\n",
		temac_indirect_in32(lp, XTE_MC_OFFSET));
	return 0;
}