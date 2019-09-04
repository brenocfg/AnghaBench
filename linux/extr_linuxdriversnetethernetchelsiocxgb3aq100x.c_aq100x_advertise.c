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
 unsigned int ADVERTISED_10000baseT_Full ; 
 unsigned int ADVERTISED_1000baseT_Full ; 
 unsigned int ADVERTISED_1000baseT_Half ; 
 unsigned int ADVERTISED_100baseT_Full ; 
 unsigned int ADVERTISED_100baseT_Half ; 
 unsigned int ADVERTISED_Asym_Pause ; 
 unsigned int ADVERTISED_Pause ; 
 unsigned int ADVERTISE_100FULL ; 
 unsigned int ADVERTISE_100HALF ; 
 unsigned int ADVERTISE_PAUSE_ASYM ; 
 unsigned int ADVERTISE_PAUSE_CAP ; 
 unsigned int ADV_10G_FULL ; 
 unsigned int ADV_1G_FULL ; 
 unsigned int ADV_1G_HALF ; 
 int /*<<< orphan*/  AQ_1G_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int aq100x_advertise(struct cphy *phy, unsigned int advertise_map)
{
	unsigned int adv;
	int err;

	/* 10G advertisement */
	adv = 0;
	if (advertise_map & ADVERTISED_10000baseT_Full)
		adv |= ADV_10G_FULL;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
				  ADV_10G_FULL, adv);
	if (err)
		return err;

	/* 1G advertisement */
	adv = 0;
	if (advertise_map & ADVERTISED_1000baseT_Full)
		adv |= ADV_1G_FULL;
	if (advertise_map & ADVERTISED_1000baseT_Half)
		adv |= ADV_1G_HALF;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, AQ_1G_CTRL,
				  ADV_1G_FULL | ADV_1G_HALF, adv);
	if (err)
		return err;

	/* 100M, pause advertisement */
	adv = 0;
	if (advertise_map & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	if (advertise_map & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	if (advertise_map & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	if (advertise_map & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_ADVERTISE,
				  0xfe0, adv);

	return err;
}