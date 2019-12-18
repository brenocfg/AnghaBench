#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct bgmac {int /*<<< orphan*/  dev; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  phyaddr; TYPE_1__* mii_bus; } ;
typedef  int /*<<< orphan*/  bus_id ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  bgmac_adjust_link ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct phy_device* phy_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcma_phy_connect(struct bgmac *bgmac)
{
	struct phy_device *phy_dev;
	char bus_id[MII_BUS_ID_SIZE + 3];

	/* Connect to the PHY */
	snprintf(bus_id, sizeof(bus_id), PHY_ID_FMT, bgmac->mii_bus->id,
		 bgmac->phyaddr);
	phy_dev = phy_connect(bgmac->net_dev, bus_id, bgmac_adjust_link,
			      PHY_INTERFACE_MODE_MII);
	if (IS_ERR(phy_dev)) {
		dev_err(bgmac->dev, "PHY connection failed\n");
		return PTR_ERR(phy_dev);
	}

	return 0;
}