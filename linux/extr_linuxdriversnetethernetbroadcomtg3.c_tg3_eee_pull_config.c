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
struct ethtool_eee {int eee_active; int eee_enabled; int tx_lpi_enabled; int tx_lpi_timer; void* advertised; void* lp_advertised; } ;
struct tg3 {int phy_flags; struct ethtool_eee eee; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_EEE_LPABLE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  TG3_CL45_D7_EEERES_STAT ; 
 int TG3_CL45_D7_EEERES_STAT_LP_1000T ; 
 int TG3_CL45_D7_EEERES_STAT_LP_100TX ; 
 int TG3_CPMU_EEEMD_LPI_IN_TX ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_DBTMR1 ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_MODE ; 
 int TG3_PHYFLG_EEE_CAP ; 
 void* mmd_eee_adv_to_ethtool_adv_t (int) ; 
 scalar_t__ tg3_phy_cl45_read (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_eee_pull_config(struct tg3 *tp, struct ethtool_eee *eee)
{
	u32 val;
	struct ethtool_eee *dest = &tp->eee;

	if (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		return;

	if (eee)
		dest = eee;

	if (tg3_phy_cl45_read(tp, MDIO_MMD_AN, TG3_CL45_D7_EEERES_STAT, &val))
		return;

	/* Pull eee_active */
	if (val == TG3_CL45_D7_EEERES_STAT_LP_1000T ||
	    val == TG3_CL45_D7_EEERES_STAT_LP_100TX) {
		dest->eee_active = 1;
	} else
		dest->eee_active = 0;

	/* Pull lp advertised settings */
	if (tg3_phy_cl45_read(tp, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE, &val))
		return;
	dest->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	/* Pull advertised and eee_enabled settings */
	if (tg3_phy_cl45_read(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, &val))
		return;
	dest->eee_enabled = !!val;
	dest->advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	/* Pull tx_lpi_enabled */
	val = tr32(TG3_CPMU_EEE_MODE);
	dest->tx_lpi_enabled = !!(val & TG3_CPMU_EEEMD_LPI_IN_TX);

	/* Pull lpi timer value */
	dest->tx_lpi_timer = tr32(TG3_CPMU_EEE_DBTMR1) & 0xffff;
}