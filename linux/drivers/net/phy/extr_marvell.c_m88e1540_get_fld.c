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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETHTOOL_PHY_FAST_LINK_DOWN_OFF ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MII_88E1540_COPPER_CTRL3 ; 
 int MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN ; 
#define  MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_00MS 131 
#define  MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_10MS 130 
#define  MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_20MS 129 
#define  MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_40MS 128 
 int /*<<< orphan*/  MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1540_get_fld(struct phy_device *phydev, u8 *msecs)
{
	int val;

	val = phy_read(phydev, MII_88E1540_COPPER_CTRL3);
	if (val < 0)
		return val;

	if (!(val & MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN)) {
		*msecs = ETHTOOL_PHY_FAST_LINK_DOWN_OFF;
		return 0;
	}

	val = FIELD_GET(MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK, val);

	switch (val) {
	case MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_00MS:
		*msecs = 0;
		break;
	case MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_10MS:
		*msecs = 10;
		break;
	case MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_20MS:
		*msecs = 20;
		break;
	case MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_40MS:
		*msecs = 40;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}