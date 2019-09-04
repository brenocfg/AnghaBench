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
 unsigned int ADVERTISED_Asym_Pause ; 
 unsigned int ADVERTISED_Pause ; 
 unsigned int ADVERTISE_1000XFULL ; 
 unsigned int ADVERTISE_1000XHALF ; 
 unsigned int ADVERTISE_1000XPAUSE ; 
 unsigned int ADVERTISE_1000XPSE_ASYM ; 
 int /*<<< orphan*/  MDIO_DEVAD_NONE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int t3_phy_advertise_fiber(struct cphy *phy, unsigned int advert)
{
	unsigned int val = 0;

	if (advert & ADVERTISED_1000baseT_Half)
		val |= ADVERTISE_1000XHALF;
	if (advert & ADVERTISED_1000baseT_Full)
		val |= ADVERTISE_1000XFULL;
	if (advert & ADVERTISED_Pause)
		val |= ADVERTISE_1000XPAUSE;
	if (advert & ADVERTISED_Asym_Pause)
		val |= ADVERTISE_1000XPSE_ASYM;
	return t3_mdio_write(phy, MDIO_DEVAD_NONE, MII_ADVERTISE, val);
}