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
typedef  int u32 ;
typedef  enum ixgbe_phy_type { ____Placeholder_ixgbe_phy_type } ixgbe_phy_type ;

/* Variables and functions */
#define  ATH_PHY_ID 135 
#define  QT2022_PHY_ID 134 
#define  TN1010_PHY_ID 133 
#define  X540_PHY_ID 132 
#define  X550_PHY_ID2 131 
#define  X550_PHY_ID3 130 
#define  X557_PHY_ID 129 
#define  X557_PHY_ID2 128 
 int ixgbe_phy_aq ; 
 int ixgbe_phy_nl ; 
 int ixgbe_phy_qt ; 
 int ixgbe_phy_tn ; 
 int ixgbe_phy_unknown ; 
 int ixgbe_phy_x550em_ext_t ; 

__attribute__((used)) static enum ixgbe_phy_type ixgbe_get_phy_type_from_id(u32 phy_id)
{
	enum ixgbe_phy_type phy_type;

	switch (phy_id) {
	case TN1010_PHY_ID:
		phy_type = ixgbe_phy_tn;
		break;
	case X550_PHY_ID2:
	case X550_PHY_ID3:
	case X540_PHY_ID:
		phy_type = ixgbe_phy_aq;
		break;
	case QT2022_PHY_ID:
		phy_type = ixgbe_phy_qt;
		break;
	case ATH_PHY_ID:
		phy_type = ixgbe_phy_nl;
		break;
	case X557_PHY_ID:
	case X557_PHY_ID2:
		phy_type = ixgbe_phy_x550em_ext_t;
		break;
	default:
		phy_type = ixgbe_phy_unknown;
		break;
	}

	return phy_type;
}