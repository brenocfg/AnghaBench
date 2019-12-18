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
struct tenxpress_phy_data {int bad_lp_tries; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; struct tenxpress_phy_data* phy_data; } ;

/* Variables and functions */
 int MAX_BAD_LP_TRIES ; 
 int MDIO_AN_STAT1_COMPLETE ; 
 int MDIO_AN_STAT1_LPABLE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int PMA_PMD_LED_FLASH ; 
 int PMA_PMD_LED_MASK ; 
 int PMA_PMD_LED_OFF ; 
 int /*<<< orphan*/  PMA_PMD_LED_OVERR_REG ; 
 int PMA_PMD_LED_RX_LBN ; 
 int ef4_mdio_read (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sfx7101_check_bad_lp(struct ef4_nic *efx, bool link_ok)
{
	struct tenxpress_phy_data *pd = efx->phy_data;
	bool bad_lp;
	int reg;

	if (link_ok) {
		bad_lp = false;
	} else {
		/* Check that AN has started but not completed. */
		reg = ef4_mdio_read(efx, MDIO_MMD_AN, MDIO_STAT1);
		if (!(reg & MDIO_AN_STAT1_LPABLE))
			return; /* LP status is unknown */
		bad_lp = !(reg & MDIO_AN_STAT1_COMPLETE);
		if (bad_lp)
			pd->bad_lp_tries++;
	}

	/* Nothing to do if all is well and was previously so. */
	if (!pd->bad_lp_tries)
		return;

	/* Use the RX (red) LED as an error indicator once we've seen AN
	 * failure several times in a row, and also log a message. */
	if (!bad_lp || pd->bad_lp_tries == MAX_BAD_LP_TRIES) {
		reg = ef4_mdio_read(efx, MDIO_MMD_PMAPMD,
				    PMA_PMD_LED_OVERR_REG);
		reg &= ~(PMA_PMD_LED_MASK << PMA_PMD_LED_RX_LBN);
		if (!bad_lp) {
			reg |= PMA_PMD_LED_OFF << PMA_PMD_LED_RX_LBN;
		} else {
			reg |= PMA_PMD_LED_FLASH << PMA_PMD_LED_RX_LBN;
			netif_err(efx, link, efx->net_dev,
				  "appears to be plugged into a port"
				  " that is not 10GBASE-T capable. The PHY"
				  " supports 10GBASE-T ONLY, so no link can"
				  " be established\n");
		}
		ef4_mdio_write(efx, MDIO_MMD_PMAPMD,
			       PMA_PMD_LED_OVERR_REG, reg);
		pd->bad_lp_tries = bad_lp;
	}
}