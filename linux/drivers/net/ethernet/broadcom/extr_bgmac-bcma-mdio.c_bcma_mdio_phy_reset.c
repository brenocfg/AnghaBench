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
typedef  scalar_t__ u8 ;
struct mii_bus {struct bgmac* priv; } ;
struct bgmac {scalar_t__ phyaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BGMAC_PHY_NOREGS ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  bcma_mdio_phy_init (struct bgmac*) ; 
 int bcma_mdio_phy_read (struct bgmac*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_mdio_phy_write (struct bgmac*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcma_mdio_phy_reset(struct mii_bus *bus)
{
	struct bgmac *bgmac = bus->priv;
	u8 phyaddr = bgmac->phyaddr;

	if (phyaddr == BGMAC_PHY_NOREGS)
		return 0;

	bcma_mdio_phy_write(bgmac, phyaddr, MII_BMCR, BMCR_RESET);
	udelay(100);
	if (bcma_mdio_phy_read(bgmac, phyaddr, MII_BMCR) & BMCR_RESET)
		dev_err(bgmac->dev, "PHY reset failed\n");
	bcma_mdio_phy_init(bgmac);

	return 0;
}