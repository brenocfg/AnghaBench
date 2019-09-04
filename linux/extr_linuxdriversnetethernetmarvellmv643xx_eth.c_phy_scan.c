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
struct phy_device {int dummy; } ;
struct mv643xx_eth_private {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phy_id ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int MV643XX_ETH_PHY_ADDR_DEFAULT ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  get_phy_mode (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  mv643xx_eth_adjust_link ; 
 int phy_addr_get (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  phy_addr_set (struct mv643xx_eth_private*,int) ; 
 struct phy_device* phy_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static struct phy_device *phy_scan(struct mv643xx_eth_private *mp,
				   int phy_addr)
{
	struct phy_device *phydev;
	int start;
	int num;
	int i;
	char phy_id[MII_BUS_ID_SIZE + 3];

	if (phy_addr == MV643XX_ETH_PHY_ADDR_DEFAULT) {
		start = phy_addr_get(mp) & 0x1f;
		num = 32;
	} else {
		start = phy_addr & 0x1f;
		num = 1;
	}

	/* Attempt to connect to the PHY using orion-mdio */
	phydev = ERR_PTR(-ENODEV);
	for (i = 0; i < num; i++) {
		int addr = (start + i) & 0x1f;

		snprintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
				"orion-mdio-mii", addr);

		phydev = phy_connect(mp->dev, phy_id, mv643xx_eth_adjust_link,
				     get_phy_mode(mp));
		if (!IS_ERR(phydev)) {
			phy_addr_set(mp, addr);
			break;
		}
	}

	return phydev;
}