#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mdio_device {scalar_t__ addr; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct b53_device {int current_page; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int B53_BRCM_OUI_1 ; 
 int B53_BRCM_OUI_2 ; 
 int B53_BRCM_OUI_3 ; 
 int B53_BRCM_OUI_4 ; 
 scalar_t__ BRCM_PSEUDO_PHY_ADDR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  b53_mdio_ops ; 
 struct b53_device* b53_switch_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int b53_switch_register (struct b53_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct b53_device*) ; 
 int mdiobus_read (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int b53_mdio_probe(struct mdio_device *mdiodev)
{
	struct b53_device *dev;
	u32 phy_id;
	int ret;

	/* allow the generic PHY driver to take over the non-management MDIO
	 * addresses
	 */
	if (mdiodev->addr != BRCM_PSEUDO_PHY_ADDR && mdiodev->addr != 0) {
		dev_err(&mdiodev->dev, "leaving address %d to PHY\n",
			mdiodev->addr);
		return -ENODEV;
	}

	/* read the first port's id */
	phy_id = mdiobus_read(mdiodev->bus, 0, 2) << 16;
	phy_id |= mdiobus_read(mdiodev->bus, 0, 3);

	/* BCM5325, BCM539x (OUI_1)
	 * BCM53125, BCM53128 (OUI_2)
	 * BCM5365 (OUI_3)
	 */
	if ((phy_id & 0xfffffc00) != B53_BRCM_OUI_1 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_2 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_3 &&
	    (phy_id & 0xfffffc00) != B53_BRCM_OUI_4) {
		dev_err(&mdiodev->dev, "Unsupported device: 0x%08x\n", phy_id);
		return -ENODEV;
	}

	/* First probe will come from SWITCH_MDIO controller on the 7445D0
	 * switch, which will conflict with the 7445 integrated switch
	 * pseudo-phy (we end-up programming both). In that case, we return
	 * -EPROBE_DEFER for the first time we get here, and wait until we come
	 * back with the slave MDIO bus which has the correct indirection
	 * layer setup
	 */
	if (of_machine_is_compatible("brcm,bcm7445d0") &&
	    strcmp(mdiodev->bus->name, "sf2 slave mii"))
		return -EPROBE_DEFER;

	dev = b53_switch_alloc(&mdiodev->dev, &b53_mdio_ops, mdiodev->bus);
	if (!dev)
		return -ENOMEM;

	/* we don't use page 0xff, so force a page set */
	dev->current_page = 0xff;
	dev->bus = mdiodev->bus;

	dev_set_drvdata(&mdiodev->dev, dev);

	ret = b53_switch_register(dev);
	if (ret) {
		dev_err(&mdiodev->dev, "failed to register switch: %i\n", ret);
		return ret;
	}

	return ret;
}