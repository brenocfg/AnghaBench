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
struct mii_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_id; int /*<<< orphan*/  dev; scalar_t__ supports_gmii; } ;

/* Variables and functions */
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int BMSR_ANEGCOMPLETE ; 
 int LPA_1000FULL ; 
 int LPA_1000HALF ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  mii_link_ok (struct mii_if_info*) ; 
 int mii_nway_result (int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mii_speed(struct mii_if_info *mii)
{
	int advert, lpa, val, media;
	int lpa2 = 0;
	int speed;

	if (!mii_link_ok(mii))
		return 0;

	val = (*mii->mdio_read) (mii->dev, mii->phy_id, MII_BMSR);
	if ((val & BMSR_ANEGCOMPLETE) == 0)
		return 0;

	advert = (*mii->mdio_read) (mii->dev, mii->phy_id, MII_ADVERTISE);
	lpa = (*mii->mdio_read) (mii->dev, mii->phy_id, MII_LPA);
	media = mii_nway_result(advert & lpa);

	if (mii->supports_gmii)
		lpa2 = mii->mdio_read(mii->dev, mii->phy_id, MII_STAT1000);

	speed = lpa2 & (LPA_1000FULL | LPA_1000HALF) ? 1000 :
			(media & (ADVERTISE_100FULL | ADVERTISE_100HALF) ? 100 : 10);
	return speed;
}