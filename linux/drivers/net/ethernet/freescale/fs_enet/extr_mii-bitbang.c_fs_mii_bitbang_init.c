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
struct resource {int start; } ;
struct mii_bus {int /*<<< orphan*/  id; struct bb_info* priv; } ;
struct device_node {int dummy; } ;
struct bb_info {int mdio_msk; int mdc_msk; scalar_t__ dir; scalar_t__ dat; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ ioremap (int,int) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fs_mii_bitbang_init(struct mii_bus *bus, struct device_node *np)
{
	struct resource res;
	const u32 *data;
	int mdio_pin, mdc_pin, len;
	struct bb_info *bitbang = bus->priv;

	int ret = of_address_to_resource(np, 0, &res);
	if (ret)
		return ret;

	if (resource_size(&res) <= 13)
		return -ENODEV;

	/* This should really encode the pin number as well, but all
	 * we get is an int, and the odds of multiple bitbang mdio buses
	 * is low enough that it's not worth going too crazy.
	 */
	snprintf(bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	data = of_get_property(np, "fsl,mdio-pin", &len);
	if (!data || len != 4)
		return -ENODEV;
	mdio_pin = *data;

	data = of_get_property(np, "fsl,mdc-pin", &len);
	if (!data || len != 4)
		return -ENODEV;
	mdc_pin = *data;

	bitbang->dir = ioremap(res.start, resource_size(&res));
	if (!bitbang->dir)
		return -ENOMEM;

	bitbang->dat = bitbang->dir + 4;
	bitbang->mdio_msk = 1 << (31 - mdio_pin);
	bitbang->mdc_msk = 1 << (31 - mdc_pin);

	return 0;
}