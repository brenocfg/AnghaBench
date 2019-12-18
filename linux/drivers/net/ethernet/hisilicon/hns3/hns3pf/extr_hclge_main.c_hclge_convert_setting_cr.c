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
typedef  int u8 ;
struct hclge_mac {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT ; 
 int HCLGE_SUPPORT_100G_BIT ; 
 int HCLGE_SUPPORT_10G_BIT ; 
 int HCLGE_SUPPORT_25G_BIT ; 
 int HCLGE_SUPPORT_40G_BIT ; 
 int HCLGE_SUPPORT_50G_BIT ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_convert_setting_cr(struct hclge_mac *mac, u8 speed_ability)
{
	if (speed_ability & HCLGE_SUPPORT_10G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
				 mac->supported);
	if (speed_ability & HCLGE_SUPPORT_25G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
				 mac->supported);
	if (speed_ability & HCLGE_SUPPORT_40G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
				 mac->supported);
	if (speed_ability & HCLGE_SUPPORT_50G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
				 mac->supported);
	if (speed_ability & HCLGE_SUPPORT_100G_BIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
				 mac->supported);
}