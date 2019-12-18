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
struct fman_mac {int /*<<< orphan*/  pcsphy; } ;
struct fixed_phy_status {int speed; int /*<<< orphan*/  duplex; } ;

/* Variables and functions */
 int IF_MODE_SGMII_DUPLEX_HALF ; 
 int IF_MODE_SGMII_EN ; 
 int IF_MODE_SGMII_SPEED_100M ; 
 int IF_MODE_SGMII_SPEED_1G ; 
 int IF_MODE_USE_SGMII_AN ; 
 int LINK_TMR_H ; 
 int LINK_TMR_L ; 
 int MDIO_SGMII_DEV_ABIL_SGMII ; 
 int MDIO_SGMII_DEV_ABIL_SGMII_MODE ; 
 int MDIO_SGMII_IF_MODE ; 
 int MDIO_SGMII_LINK_TMR_H ; 
 int MDIO_SGMII_LINK_TMR_L ; 
 int SGMII_CR_AN_EN ; 
 int SGMII_CR_DEF_VAL ; 
 int SGMII_CR_RESTART_AN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void setup_sgmii_internal_phy(struct fman_mac *memac,
				     struct fixed_phy_status *fixed_link)
{
	u16 tmp_reg16;

	if (WARN_ON(!memac->pcsphy))
		return;

	/* SGMII mode */
	tmp_reg16 = IF_MODE_SGMII_EN;
	if (!fixed_link)
		/* AN enable */
		tmp_reg16 |= IF_MODE_USE_SGMII_AN;
	else {
		switch (fixed_link->speed) {
		case 10:
			/* For 10M: IF_MODE[SPEED_10M] = 0 */
		break;
		case 100:
			tmp_reg16 |= IF_MODE_SGMII_SPEED_100M;
		break;
		case 1000: /* fallthrough */
		default:
			tmp_reg16 |= IF_MODE_SGMII_SPEED_1G;
		break;
		}
		if (!fixed_link->duplex)
			tmp_reg16 |= IF_MODE_SGMII_DUPLEX_HALF;
	}
	phy_write(memac->pcsphy, MDIO_SGMII_IF_MODE, tmp_reg16);

	/* Device ability according to SGMII specification */
	tmp_reg16 = MDIO_SGMII_DEV_ABIL_SGMII_MODE;
	phy_write(memac->pcsphy, MDIO_SGMII_DEV_ABIL_SGMII, tmp_reg16);

	/* Adjust link timer for SGMII  -
	 * According to Cisco SGMII specification the timer should be 1.6 ms.
	 * The link_timer register is configured in units of the clock.
	 * - When running as 1G SGMII, Serdes clock is 125 MHz, so
	 * unit = 1 / (125*10^6 Hz) = 8 ns.
	 * 1.6 ms in units of 8 ns = 1.6ms / 8ns = 2*10^5 = 0x30d40
	 * - When running as 2.5G SGMII, Serdes clock is 312.5 MHz, so
	 * unit = 1 / (312.5*10^6 Hz) = 3.2 ns.
	 * 1.6 ms in units of 3.2 ns = 1.6ms / 3.2ns = 5*10^5 = 0x7a120.
	 * Since link_timer value of 1G SGMII will be too short for 2.5 SGMII,
	 * we always set up here a value of 2.5 SGMII.
	 */
	phy_write(memac->pcsphy, MDIO_SGMII_LINK_TMR_H, LINK_TMR_H);
	phy_write(memac->pcsphy, MDIO_SGMII_LINK_TMR_L, LINK_TMR_L);

	if (!fixed_link)
		/* Restart AN */
		tmp_reg16 = SGMII_CR_DEF_VAL | SGMII_CR_RESTART_AN;
	else
		/* AN disabled */
		tmp_reg16 = SGMII_CR_DEF_VAL & ~SGMII_CR_AN_EN;
	phy_write(memac->pcsphy, 0x0, tmp_reg16);
}