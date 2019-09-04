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
 unsigned int ADVERTISED_1000baseT_Full ; 
 unsigned int ADVERTISED_1000baseT_Half ; 
 unsigned int ADVERTISED_100baseT_Full ; 
 unsigned int ADVERTISED_100baseT_Half ; 
 unsigned int ADVERTISED_10baseT_Full ; 
 unsigned int ADVERTISED_10baseT_Half ; 
 unsigned int ADVERTISED_Asym_Pause ; 
 unsigned int ADVERTISED_Pause ; 
 unsigned int ADVERTISE_1000FULL ; 
 unsigned int ADVERTISE_1000HALF ; 
 unsigned int ADVERTISE_100FULL ; 
 unsigned int ADVERTISE_100HALF ; 
 unsigned int ADVERTISE_10FULL ; 
 unsigned int ADVERTISE_10HALF ; 
 unsigned int ADVERTISE_PAUSE_ASYM ; 
 unsigned int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  MDIO_DEVAD_NONE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int t3_phy_advertise(struct cphy *phy, unsigned int advert)
{
	int err;
	unsigned int val = 0;

	err = t3_mdio_read(phy, MDIO_DEVAD_NONE, MII_CTRL1000, &val);
	if (err)
		return err;

	val &= ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
	if (advert & ADVERTISED_1000baseT_Half)
		val |= ADVERTISE_1000HALF;
	if (advert & ADVERTISED_1000baseT_Full)
		val |= ADVERTISE_1000FULL;

	err = t3_mdio_write(phy, MDIO_DEVAD_NONE, MII_CTRL1000, val);
	if (err)
		return err;

	val = 1;
	if (advert & ADVERTISED_10baseT_Half)
		val |= ADVERTISE_10HALF;
	if (advert & ADVERTISED_10baseT_Full)
		val |= ADVERTISE_10FULL;
	if (advert & ADVERTISED_100baseT_Half)
		val |= ADVERTISE_100HALF;
	if (advert & ADVERTISED_100baseT_Full)
		val |= ADVERTISE_100FULL;
	if (advert & ADVERTISED_Pause)
		val |= ADVERTISE_PAUSE_CAP;
	if (advert & ADVERTISED_Asym_Pause)
		val |= ADVERTISE_PAUSE_ASYM;
	return t3_mdio_write(phy, MDIO_DEVAD_NONE, MII_ADVERTISE, val);
}