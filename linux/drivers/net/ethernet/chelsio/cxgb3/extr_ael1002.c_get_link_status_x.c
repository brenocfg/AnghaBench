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
struct cphy {int dummy; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PCS_10GBX_STAT1 ; 
 int /*<<< orphan*/  MDIO_PHYXS_LNSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_RXDET ; 
 int SPEED_10000 ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int get_link_status_x(struct cphy *phy, int *link_ok, int *speed,
			     int *duplex, int *fc)
{
	if (link_ok) {
		unsigned int stat0, stat1, stat2;
		int err = t3_mdio_read(phy, MDIO_MMD_PMAPMD,
				       MDIO_PMA_RXDET, &stat0);

		if (!err)
			err = t3_mdio_read(phy, MDIO_MMD_PCS,
					   MDIO_PCS_10GBX_STAT1, &stat1);
		if (!err)
			err = t3_mdio_read(phy, MDIO_MMD_PHYXS,
					   MDIO_PHYXS_LNSTAT, &stat2);
		if (err)
			return err;
		*link_ok = (stat0 & (stat1 >> 12) & (stat2 >> 12)) & 1;
	}
	if (speed)
		*speed = SPEED_10000;
	if (duplex)
		*duplex = DUPLEX_FULL;
	return 0;
}