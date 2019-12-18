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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  fwnode; struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; int /*<<< orphan*/  reset_deassert_delay; int /*<<< orphan*/  reset_assert_delay; } ;
struct phy_device {int irq; TYPE_2__ mdio; } ;
struct mii_bus {int* irq; int phy_ignore_ta_mask; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct device_node*,size_t) ; 
 struct phy_device* get_phy_device (struct mii_bus*,size_t,int) ; 
 int of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int /*<<< orphan*/  of_get_phy_id (struct device_node*,size_t*) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct phy_device* phy_device_create (struct mii_bus*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int phy_device_register (struct phy_device*) ; 

__attribute__((used)) static int of_mdiobus_register_phy(struct mii_bus *mdio,
				    struct device_node *child, u32 addr)
{
	struct phy_device *phy;
	bool is_c45;
	int rc;
	u32 phy_id;

	is_c45 = of_device_is_compatible(child,
					 "ethernet-phy-ieee802.3-c45");

	if (!is_c45 && !of_get_phy_id(child, &phy_id))
		phy = phy_device_create(mdio, addr, phy_id, 0, NULL);
	else
		phy = get_phy_device(mdio, addr, is_c45);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	rc = of_irq_get(child, 0);
	if (rc == -EPROBE_DEFER) {
		phy_device_free(phy);
		return rc;
	}
	if (rc > 0) {
		phy->irq = rc;
		mdio->irq[addr] = rc;
	} else {
		phy->irq = mdio->irq[addr];
	}

	if (of_property_read_bool(child, "broken-turn-around"))
		mdio->phy_ignore_ta_mask |= 1 << addr;

	of_property_read_u32(child, "reset-assert-us",
			     &phy->mdio.reset_assert_delay);
	of_property_read_u32(child, "reset-deassert-us",
			     &phy->mdio.reset_deassert_delay);

	/* Associate the OF node with the device structure so it
	 * can be looked up later */
	of_node_get(child);
	phy->mdio.dev.of_node = child;
	phy->mdio.dev.fwnode = of_fwnode_handle(child);

	/* All data is now stored in the phy struct;
	 * register it */
	rc = phy_device_register(phy);
	if (rc) {
		phy_device_free(phy);
		of_node_put(child);
		return rc;
	}

	dev_dbg(&mdio->dev, "registered phy %pOFn at address %i\n",
		child, addr);
	return 0;
}