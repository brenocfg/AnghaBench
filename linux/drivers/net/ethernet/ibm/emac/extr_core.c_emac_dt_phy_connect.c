#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  address; int /*<<< orphan*/  features; TYPE_6__* def; } ;
struct emac_instance {TYPE_5__* phy_dev; TYPE_4__ phy; TYPE_1__* ofdev; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  ndev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; int /*<<< orphan*/  phy_id_mask; int /*<<< orphan*/  phy_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  interface; TYPE_3__ mdio; int /*<<< orphan*/  supported; TYPE_2__* drv; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  phy_id_mask; int /*<<< orphan*/  phy_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_6__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_adjust_link ; 
 int /*<<< orphan*/  emac_dt_mdio_phy_ops ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_dt_phy_connect(struct emac_instance *dev,
			       struct device_node *phy_handle)
{
	dev->phy.def = devm_kzalloc(&dev->ofdev->dev, sizeof(*dev->phy.def),
				    GFP_KERNEL);
	if (!dev->phy.def)
		return -ENOMEM;

	dev->phy_dev = of_phy_connect(dev->ndev, phy_handle, &emac_adjust_link,
				      0, dev->phy_mode);
	if (!dev->phy_dev) {
		dev_err(&dev->ofdev->dev, "failed to connect to PHY.\n");
		return -ENODEV;
	}

	dev->phy.def->phy_id = dev->phy_dev->drv->phy_id;
	dev->phy.def->phy_id_mask = dev->phy_dev->drv->phy_id_mask;
	dev->phy.def->name = dev->phy_dev->drv->name;
	dev->phy.def->ops = &emac_dt_mdio_phy_ops;
	ethtool_convert_link_mode_to_legacy_u32(&dev->phy.features,
						dev->phy_dev->supported);
	dev->phy.address = dev->phy_dev->mdio.addr;
	dev->phy.mode = dev->phy_dev->interface;
	return 0;
}