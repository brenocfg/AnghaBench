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
struct mii_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMSR_ESTATEN ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mii_check_gmii_support(struct mii_if_info *mii)
{
	int reg;

	reg = mii->mdio_read(mii->dev, mii->phy_id, MII_BMSR);
	if (reg & BMSR_ESTATEN) {
		reg = mii->mdio_read(mii->dev, mii->phy_id, MII_ESTATUS);
		if (reg & (ESTATUS_1000_TFULL | ESTATUS_1000_THALF))
			return 1;
	}

	return 0;
}