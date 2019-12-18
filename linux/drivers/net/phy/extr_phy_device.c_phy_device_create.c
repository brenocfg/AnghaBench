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
struct phy_c45_device_ids {int* device_ids; int devices_in_package; } ;
struct TYPE_3__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct mdio_device {int addr; TYPE_1__ dev; int /*<<< orphan*/  device_remove; int /*<<< orphan*/  device_free; int /*<<< orphan*/  flags; int /*<<< orphan*/  bus_match; struct mii_bus* bus; } ;
struct phy_device {int duplex; int is_c45; int phy_id; int /*<<< orphan*/  state_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  irq; struct phy_c45_device_ids c45_ids; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  interface; scalar_t__ link; scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ speed; struct mdio_device mdio; } ;
struct mii_bus {int /*<<< orphan*/  id; int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int ENOMEM ; 
 struct phy_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_DEVICE_FLAG_PHY ; 
 int /*<<< orphan*/  PHY_DOWN ; 
 int /*<<< orphan*/  PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct phy_device*) ; 
 struct phy_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_bus_phy_type ; 
 int /*<<< orphan*/  mdio_bus_type ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_bus_match ; 
 int /*<<< orphan*/  phy_mdio_device_free ; 
 int /*<<< orphan*/  phy_mdio_device_remove ; 
 int phy_request_driver_module (struct phy_device*,int) ; 
 int /*<<< orphan*/  phy_state_machine ; 

struct phy_device *phy_device_create(struct mii_bus *bus, int addr, int phy_id,
				     bool is_c45,
				     struct phy_c45_device_ids *c45_ids)
{
	struct phy_device *dev;
	struct mdio_device *mdiodev;
	int ret = 0;

	/* We allocate the device, and initialize the default values */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	mdiodev = &dev->mdio;
	mdiodev->dev.parent = &bus->dev;
	mdiodev->dev.bus = &mdio_bus_type;
	mdiodev->dev.type = &mdio_bus_phy_type;
	mdiodev->bus = bus;
	mdiodev->bus_match = phy_bus_match;
	mdiodev->addr = addr;
	mdiodev->flags = MDIO_DEVICE_FLAG_PHY;
	mdiodev->device_free = phy_mdio_device_free;
	mdiodev->device_remove = phy_mdio_device_remove;

	dev->speed = 0;
	dev->duplex = -1;
	dev->pause = 0;
	dev->asym_pause = 0;
	dev->link = 0;
	dev->interface = PHY_INTERFACE_MODE_GMII;

	dev->autoneg = AUTONEG_ENABLE;

	dev->is_c45 = is_c45;
	dev->phy_id = phy_id;
	if (c45_ids)
		dev->c45_ids = *c45_ids;
	dev->irq = bus->irq[addr];
	dev_set_name(&mdiodev->dev, PHY_ID_FMT, bus->id, addr);

	dev->state = PHY_DOWN;

	mutex_init(&dev->lock);
	INIT_DELAYED_WORK(&dev->state_queue, phy_state_machine);

	/* Request the appropriate module unconditionally; don't
	 * bother trying to do so only if it isn't already loaded,
	 * because that gets complicated. A hotplug event would have
	 * done an unconditional modprobe anyway.
	 * We don't do normal hotplug because it won't work for MDIO
	 * -- because it relies on the device staying around for long
	 * enough for the driver to get loaded. With MDIO, the NIC
	 * driver will get bored and give up as soon as it finds that
	 * there's no driver _already_ loaded.
	 */
	if (is_c45 && c45_ids) {
		const int num_ids = ARRAY_SIZE(c45_ids->device_ids);
		int i;

		for (i = 1; i < num_ids; i++) {
			if (!(c45_ids->devices_in_package & (1 << i)))
				continue;

			ret = phy_request_driver_module(dev,
						c45_ids->device_ids[i]);
			if (ret)
				break;
		}
	} else {
		ret = phy_request_driver_module(dev, phy_id);
	}

	if (!ret) {
		device_initialize(&mdiodev->dev);
	} else {
		kfree(dev);
		dev = ERR_PTR(ret);
	}

	return dev;
}