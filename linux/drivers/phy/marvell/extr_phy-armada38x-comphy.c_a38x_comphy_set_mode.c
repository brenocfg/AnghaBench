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
struct phy {int dummy; } ;
struct a38x_comphy_lane {int dummy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int /*<<< orphan*/  COMPHY_STAT1 ; 
 int COMPHY_STAT1_PLL_RDY_RX ; 
 int COMPHY_STAT1_PLL_RDY_TX ; 
 int EINVAL ; 
 unsigned int GEN_SGMII_1_25GBPS ; 
 unsigned int GEN_SGMII_3_125GBPS ; 
#define  PHY_INTERFACE_MODE_1000BASEX 130 
#define  PHY_INTERFACE_MODE_2500BASEX 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int PHY_MODE_ETHERNET ; 
 int a38x_comphy_poll (struct a38x_comphy_lane*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  a38x_comphy_set_speed (struct a38x_comphy_lane*,unsigned int,unsigned int) ; 
 struct a38x_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int a38x_comphy_set_mode(struct phy *phy, enum phy_mode mode, int sub)
{
	struct a38x_comphy_lane *lane = phy_get_drvdata(phy);
	unsigned int gen;

	if (mode != PHY_MODE_ETHERNET)
		return -EINVAL;

	switch (sub) {
	case PHY_INTERFACE_MODE_SGMII:
	case PHY_INTERFACE_MODE_1000BASEX:
		gen = GEN_SGMII_1_25GBPS;
		break;

	case PHY_INTERFACE_MODE_2500BASEX:
		gen = GEN_SGMII_3_125GBPS;
		break;

	default:
		return -EINVAL;
	}

	a38x_comphy_set_speed(lane, gen, gen);

	return a38x_comphy_poll(lane, COMPHY_STAT1,
				COMPHY_STAT1_PLL_RDY_TX |
				COMPHY_STAT1_PLL_RDY_RX,
				COMPHY_STAT1_PLL_RDY_TX |
				COMPHY_STAT1_PLL_RDY_RX);
}