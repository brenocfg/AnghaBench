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
struct tg3 {int phy_flags; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5704 ; 
 scalar_t__ ASIC_REV_5906 ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_PDOWN ; 
 scalar_t__ CHIPREV_5761_AX ; 
 scalar_t__ CHIPREV_5784_AX ; 
 int CPMU_LSPD_1000MB_MACCLK_12_5 ; 
 int CPMU_LSPD_1000MB_MACCLK_MASK ; 
 int /*<<< orphan*/  GRC_MISC_CFG ; 
 int GRC_MISC_CFG_EPHY_IDDQ ; 
 int /*<<< orphan*/  MAC_SERDES_CFG ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_TG3_AUXCTL_PCTL_100TX_LPWR ; 
 int MII_TG3_AUXCTL_PCTL_SPR_ISOLATE ; 
 int MII_TG3_AUXCTL_PCTL_VREG_11V ; 
 int /*<<< orphan*/  MII_TG3_AUXCTL_SHDWSEL_PWRCTL ; 
 int /*<<< orphan*/  MII_TG3_EXT_CTRL ; 
 int MII_TG3_EXT_CTRL_FORCE_LED_OFF ; 
 int MII_TG3_FET_SHADOW_EN ; 
 int /*<<< orphan*/  MII_TG3_FET_SHDW_AUXMODE4 ; 
 int MII_TG3_FET_SHDW_AUXMODE4_SBPD ; 
 int /*<<< orphan*/  MII_TG3_FET_TEST ; 
 int /*<<< orphan*/  SG_DIG_CTRL ; 
 int SG_DIG_SOFT_RESET ; 
 int SG_DIG_USING_HW_AUTONEG ; 
 int /*<<< orphan*/  TG3_CPMU_LSPD_1000MB_CLK ; 
 int TG3_PHYFLG_IS_FET ; 
 int TG3_PHYFLG_KEEP_LINK_ON_PWRDN ; 
 int TG3_PHYFLG_PHY_SERDES ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_bmcr_reset (struct tg3*) ; 
 scalar_t__ tg3_chip_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_auxctl_write (struct tg3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tg3_phy_led_bug (struct tg3*) ; 
 scalar_t__ tg3_phy_power_bug (struct tg3*) ; 
 int /*<<< orphan*/  tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tg3_power_down_phy(struct tg3 *tp, bool do_low_power)
{
	u32 val;

	if (tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN)
		return;

	if (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) {
		if (tg3_asic_rev(tp) == ASIC_REV_5704) {
			u32 sg_dig_ctrl = tr32(SG_DIG_CTRL);
			u32 serdes_cfg = tr32(MAC_SERDES_CFG);

			sg_dig_ctrl |=
				SG_DIG_USING_HW_AUTONEG | SG_DIG_SOFT_RESET;
			tw32(SG_DIG_CTRL, sg_dig_ctrl);
			tw32(MAC_SERDES_CFG, serdes_cfg | (1 << 15));
		}
		return;
	}

	if (tg3_asic_rev(tp) == ASIC_REV_5906) {
		tg3_bmcr_reset(tp);
		val = tr32(GRC_MISC_CFG);
		tw32_f(GRC_MISC_CFG, val | GRC_MISC_CFG_EPHY_IDDQ);
		udelay(40);
		return;
	} else if (tp->phy_flags & TG3_PHYFLG_IS_FET) {
		u32 phytest;
		if (!tg3_readphy(tp, MII_TG3_FET_TEST, &phytest)) {
			u32 phy;

			tg3_writephy(tp, MII_ADVERTISE, 0);
			tg3_writephy(tp, MII_BMCR,
				     BMCR_ANENABLE | BMCR_ANRESTART);

			tg3_writephy(tp, MII_TG3_FET_TEST,
				     phytest | MII_TG3_FET_SHADOW_EN);
			if (!tg3_readphy(tp, MII_TG3_FET_SHDW_AUXMODE4, &phy)) {
				phy |= MII_TG3_FET_SHDW_AUXMODE4_SBPD;
				tg3_writephy(tp,
					     MII_TG3_FET_SHDW_AUXMODE4,
					     phy);
			}
			tg3_writephy(tp, MII_TG3_FET_TEST, phytest);
		}
		return;
	} else if (do_low_power) {
		if (!tg3_phy_led_bug(tp))
			tg3_writephy(tp, MII_TG3_EXT_CTRL,
				     MII_TG3_EXT_CTRL_FORCE_LED_OFF);

		val = MII_TG3_AUXCTL_PCTL_100TX_LPWR |
		      MII_TG3_AUXCTL_PCTL_SPR_ISOLATE |
		      MII_TG3_AUXCTL_PCTL_VREG_11V;
		tg3_phy_auxctl_write(tp, MII_TG3_AUXCTL_SHDWSEL_PWRCTL, val);
	}

	/* The PHY should not be powered down on some chips because
	 * of bugs.
	 */
	if (tg3_phy_power_bug(tp))
		return;

	if (tg3_chip_rev(tp) == CHIPREV_5784_AX ||
	    tg3_chip_rev(tp) == CHIPREV_5761_AX) {
		val = tr32(TG3_CPMU_LSPD_1000MB_CLK);
		val &= ~CPMU_LSPD_1000MB_MACCLK_MASK;
		val |= CPMU_LSPD_1000MB_MACCLK_12_5;
		tw32_f(TG3_CPMU_LSPD_1000MB_CLK, val);
	}

	tg3_writephy(tp, MII_BMCR, BMCR_PDOWN);
}