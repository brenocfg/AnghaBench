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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseKX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int MDIO_EEE_1000KX ; 
 int MDIO_EEE_1000T ; 
 int MDIO_EEE_100TX ; 
 int MDIO_EEE_10GKR ; 
 int MDIO_EEE_10GKX4 ; 
 int MDIO_EEE_10GT ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  linkmode_zero (unsigned long*) ; 

__attribute__((used)) static void mmd_eee_adv_to_linkmode(unsigned long *advertising, u16 eee_adv)
{
	linkmode_zero(advertising);

	if (eee_adv & MDIO_EEE_100TX)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 advertising);
	if (eee_adv & MDIO_EEE_1000T)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 advertising);
	if (eee_adv & MDIO_EEE_10GT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				 advertising);
	if (eee_adv & MDIO_EEE_1000KX)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				 advertising);
	if (eee_adv & MDIO_EEE_10GKX4)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
				 advertising);
	if (eee_adv & MDIO_EEE_10GKR)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				 advertising);
}