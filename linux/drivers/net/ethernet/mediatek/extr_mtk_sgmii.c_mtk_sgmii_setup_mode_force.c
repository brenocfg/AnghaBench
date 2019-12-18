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
struct phylink_link_state {scalar_t__ interface; int speed; scalar_t__ duplex; } ;
struct mtk_sgmii {int /*<<< orphan*/ * regmap; int /*<<< orphan*/  ana_rgc3; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 unsigned int RG_PHY_SPEED_3_125G ; 
 unsigned int RG_PHY_SPEED_MASK ; 
 unsigned int SGMII_AN_ENABLE ; 
 unsigned int SGMII_DUPLEX_FULL ; 
 unsigned int SGMII_IF_MODE_MASK ; 
 unsigned int SGMII_PHYA_PWD ; 
 unsigned int SGMII_SPEED_10 ; 
 unsigned int SGMII_SPEED_100 ; 
 unsigned int SGMII_SPEED_1000 ; 
 int /*<<< orphan*/  SGMSYS_PCS_CONTROL_1 ; 
 int /*<<< orphan*/  SGMSYS_QPHY_PWR_STATE_CTRL ; 
 int /*<<< orphan*/  SGMSYS_SGMII_MODE ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int mtk_sgmii_setup_mode_force(struct mtk_sgmii *ss, int id,
			       const struct phylink_link_state *state)
{
	unsigned int val;

	if (!ss->regmap[id])
		return -EINVAL;

	regmap_read(ss->regmap[id], ss->ana_rgc3, &val);
	val &= ~RG_PHY_SPEED_MASK;
	if (state->interface == PHY_INTERFACE_MODE_2500BASEX)
		val |= RG_PHY_SPEED_3_125G;
	regmap_write(ss->regmap[id], ss->ana_rgc3, val);

	/* Disable SGMII AN */
	regmap_read(ss->regmap[id], SGMSYS_PCS_CONTROL_1, &val);
	val &= ~SGMII_AN_ENABLE;
	regmap_write(ss->regmap[id], SGMSYS_PCS_CONTROL_1, val);

	/* SGMII force mode setting */
	regmap_read(ss->regmap[id], SGMSYS_SGMII_MODE, &val);
	val &= ~SGMII_IF_MODE_MASK;

	switch (state->speed) {
	case SPEED_10:
		val |= SGMII_SPEED_10;
		break;
	case SPEED_100:
		val |= SGMII_SPEED_100;
		break;
	case SPEED_2500:
	case SPEED_1000:
		val |= SGMII_SPEED_1000;
		break;
	};

	if (state->duplex == DUPLEX_FULL)
		val |= SGMII_DUPLEX_FULL;

	regmap_write(ss->regmap[id], SGMSYS_SGMII_MODE, val);

	/* Release PHYA power down state */
	regmap_read(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, &val);
	val &= ~SGMII_PHYA_PWD;
	regmap_write(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, val);

	return 0;
}