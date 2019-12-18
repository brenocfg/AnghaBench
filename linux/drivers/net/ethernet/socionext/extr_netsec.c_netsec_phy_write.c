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
struct netsec_priv {int /*<<< orphan*/  freq; } ;
struct mii_bus {struct netsec_priv* priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GMAC_REG_GAR ; 
 int /*<<< orphan*/  GMAC_REG_GDR ; 
 int GMAC_REG_SHIFT_CR_GAR ; 
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int NETSEC_GMAC_GAR_REG_GB ; 
 int NETSEC_GMAC_GAR_REG_GW ; 
 int NETSEC_GMAC_GAR_REG_SHIFT_GR ; 
 int NETSEC_GMAC_GAR_REG_SHIFT_PA ; 
 int netsec_clk_type (int /*<<< orphan*/ ) ; 
 int netsec_mac_wait_while_busy (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netsec_mac_write (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netsec_phy_read (struct mii_bus*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netsec_phy_write(struct mii_bus *bus,
			    int phy_addr, int reg, u16 val)
{
	int status;
	struct netsec_priv *priv = bus->priv;

	if (netsec_mac_write(priv, GMAC_REG_GDR, val))
		return -ETIMEDOUT;
	if (netsec_mac_write(priv, GMAC_REG_GAR,
			     phy_addr << NETSEC_GMAC_GAR_REG_SHIFT_PA |
			     reg << NETSEC_GMAC_GAR_REG_SHIFT_GR |
			     NETSEC_GMAC_GAR_REG_GW | NETSEC_GMAC_GAR_REG_GB |
			     (netsec_clk_type(priv->freq) <<
			      GMAC_REG_SHIFT_CR_GAR)))
		return -ETIMEDOUT;

	status = netsec_mac_wait_while_busy(priv, GMAC_REG_GAR,
					    NETSEC_GMAC_GAR_REG_GB);

	/* Developerbox implements RTL8211E PHY and there is
	 * a compatibility problem with F_GMAC4.
	 * RTL8211E expects MDC clock must be kept toggling for several
	 * clock cycle with MDIO high before entering the IDLE state.
	 * To meet this requirement, netsec driver needs to issue dummy
	 * read(e.g. read PHYID1(offset 0x2) register) right after write.
	 */
	netsec_phy_read(bus, phy_addr, MII_PHYSID1);

	return status;
}