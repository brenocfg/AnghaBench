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

/* Variables and functions */
 int LINK_TMR_H_BASEX ; 
 int LINK_TMR_L_BASEX ; 
 int MDIO_SGMII_DEV_ABIL_BASEX_MODE ; 
 int MDIO_SGMII_DEV_ABIL_SGMII ; 
 int MDIO_SGMII_LINK_TMR_H ; 
 int MDIO_SGMII_LINK_TMR_L ; 
 int SGMII_CR_DEF_VAL ; 
 int SGMII_CR_RESTART_AN ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void setup_sgmii_internal_phy_base_x(struct fman_mac *memac)
{
	u16 tmp_reg16;

	/* AN Device capability  */
	tmp_reg16 = MDIO_SGMII_DEV_ABIL_BASEX_MODE;
	phy_write(memac->pcsphy, MDIO_SGMII_DEV_ABIL_SGMII, tmp_reg16);

	/* Adjust link timer for SGMII  -
	 * For Serdes 1000BaseX auto-negotiation the timer should be 10 ms.
	 * The link_timer register is configured in units of the clock.
	 * - When running as 1G SGMII, Serdes clock is 125 MHz, so
	 * unit = 1 / (125*10^6 Hz) = 8 ns.
	 * 10 ms in units of 8 ns = 10ms / 8ns = 1250000 = 0x1312d0
	 * - When running as 2.5G SGMII, Serdes clock is 312.5 MHz, so
	 * unit = 1 / (312.5*10^6 Hz) = 3.2 ns.
	 * 10 ms in units of 3.2 ns = 10ms / 3.2ns = 3125000 = 0x2faf08.
	 * Since link_timer value of 1G SGMII will be too short for 2.5 SGMII,
	 * we always set up here a value of 2.5 SGMII.
	 */
	phy_write(memac->pcsphy, MDIO_SGMII_LINK_TMR_H, LINK_TMR_H_BASEX);
	phy_write(memac->pcsphy, MDIO_SGMII_LINK_TMR_L, LINK_TMR_L_BASEX);

	/* Restart AN */
	tmp_reg16 = SGMII_CR_DEF_VAL | SGMII_CR_RESTART_AN;
	phy_write(memac->pcsphy, 0x0, tmp_reg16);
}