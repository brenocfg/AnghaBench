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
struct rockchip_typec_phy {scalar_t__ base; } ;
typedef  int s32 ;

/* Variables and functions */
 int CMN_CALIB_CODE (int) ; 
 int CMN_CALIB_CODE_POS (int) ; 
 scalar_t__ CMN_TXPDCAL_CTRL ; 
 scalar_t__ CMN_TXPD_ADJ_CTRL ; 
 scalar_t__ CMN_TXPUCAL_CTRL ; 
 scalar_t__ CMN_TXPU_ADJ_CTRL ; 
 scalar_t__ PHY_DP_TX_CTL ; 
 int TXDA_BGREF_EN ; 
 int TXDA_CAL_LATCH_EN ; 
 scalar_t__ TXDA_COEFF_CALC_CTRL ; 
 scalar_t__ TXDA_CYA_AUXDA_CYA ; 
 int TXDA_DECAP_EN ; 
 int TXDA_DECAP_EN_DEL ; 
 int TXDA_DP_AUX_EN ; 
 int TXDA_DRV_LDO_EN ; 
 int TXDA_DRV_PREDRV_EN ; 
 int TXDA_DRV_PREDRV_EN_DEL ; 
 int TXDA_UPHY_SUPPLY_EN ; 
 int TXDA_UPHY_SUPPLY_EN_DEL ; 
 scalar_t__ TX_ANA_CTRL_REG_1 ; 
 scalar_t__ TX_ANA_CTRL_REG_2 ; 
 scalar_t__ TX_ANA_CTRL_REG_3 ; 
 scalar_t__ TX_ANA_CTRL_REG_4 ; 
 scalar_t__ TX_ANA_CTRL_REG_5 ; 
 scalar_t__ TX_DIG_CTRL_REG_2 ; 
 int TX_HIGH_Z_TM_EN ; 
 int TX_RESCAL_CODE_MASK ; 
 int TX_RESCAL_CODE_OFFSET ; 
 int XCVR_DECAP_EN ; 
 int XCVR_DECAP_EN_DEL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tcphy_dp_aux_calibration(struct rockchip_typec_phy *tcphy)
{
	u16 val;
	u16 tx_ana_ctrl_reg_1;
	u16 tx_ana_ctrl_reg_2;
	s32 pu_calib_code, pd_calib_code;
	s32 pu_adj, pd_adj;
	u16 calib;

	/*
	 * Calculate calibration code as per docs: use an average of the
	 * pull down and pull up.  Then add in adjustments.
	 */
	val = readl(tcphy->base + CMN_TXPUCAL_CTRL);
	pu_calib_code = CMN_CALIB_CODE_POS(val);
	val = readl(tcphy->base + CMN_TXPDCAL_CTRL);
	pd_calib_code = CMN_CALIB_CODE_POS(val);
	val = readl(tcphy->base + CMN_TXPU_ADJ_CTRL);
	pu_adj = CMN_CALIB_CODE(val);
	val = readl(tcphy->base + CMN_TXPD_ADJ_CTRL);
	pd_adj = CMN_CALIB_CODE(val);
	calib = (pu_calib_code + pd_calib_code) / 2 + pu_adj + pd_adj;

	/* disable txda_cal_latch_en for rewrite the calibration values */
	tx_ana_ctrl_reg_1 = readl(tcphy->base + TX_ANA_CTRL_REG_1);
	tx_ana_ctrl_reg_1 &= ~TXDA_CAL_LATCH_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/* write the calibration, then delay 10 ms as sample in docs */
	val = readl(tcphy->base + TX_DIG_CTRL_REG_2);
	val &= ~(TX_RESCAL_CODE_MASK << TX_RESCAL_CODE_OFFSET);
	val |= calib << TX_RESCAL_CODE_OFFSET;
	writel(val, tcphy->base + TX_DIG_CTRL_REG_2);
	usleep_range(10000, 10050);

	/*
	 * Enable signal for latch that sample and holds calibration values.
	 * Activate this signal for 1 clock cycle to sample new calibration
	 * values.
	 */
	tx_ana_ctrl_reg_1 |= TXDA_CAL_LATCH_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	usleep_range(150, 200);

	/* set TX Voltage Level and TX Deemphasis to 0 */
	writel(0, tcphy->base + PHY_DP_TX_CTL);

	/* re-enable decap */
	tx_ana_ctrl_reg_2 = XCVR_DECAP_EN;
	writel(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);
	udelay(1);
	tx_ana_ctrl_reg_2 |= XCVR_DECAP_EN_DEL;
	writel(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);

	writel(0, tcphy->base + TX_ANA_CTRL_REG_3);

	tx_ana_ctrl_reg_1 |= TXDA_UPHY_SUPPLY_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(1);
	tx_ana_ctrl_reg_1 |= TXDA_UPHY_SUPPLY_EN_DEL;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	writel(0, tcphy->base + TX_ANA_CTRL_REG_5);

	/*
	 * Programs txda_drv_ldo_prog[15:0], Sets driver LDO
	 * voltage 16'h1001 for DP-AUX-TX and RX
	 */
	writel(0x1001, tcphy->base + TX_ANA_CTRL_REG_4);

	/* re-enables Bandgap reference for LDO */
	tx_ana_ctrl_reg_1 |= TXDA_DRV_LDO_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(5);
	tx_ana_ctrl_reg_1 |= TXDA_BGREF_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/*
	 * re-enables the transmitter pre-driver, driver data selection MUX,
	 * and receiver detect circuits.
	 */
	tx_ana_ctrl_reg_2 |= TXDA_DRV_PREDRV_EN;
	writel(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);
	udelay(1);
	tx_ana_ctrl_reg_2 |= TXDA_DRV_PREDRV_EN_DEL;
	writel(tx_ana_ctrl_reg_2, tcphy->base + TX_ANA_CTRL_REG_2);

	/*
	 * Do all the undocumented magic:
	 * - Turn on TXDA_DP_AUX_EN, whatever that is, even though sample
	 *   never shows this going on.
	 * - Turn on TXDA_DECAP_EN (and TXDA_DECAP_EN_DEL) even though
	 *   docs say for aux it's always 0.
	 * - Turn off the LDO and BGREF, which we just spent time turning
	 *   on above (???).
	 *
	 * Without this magic, things seem worse.
	 */
	tx_ana_ctrl_reg_1 |= TXDA_DP_AUX_EN;
	tx_ana_ctrl_reg_1 |= TXDA_DECAP_EN;
	tx_ana_ctrl_reg_1 &= ~TXDA_DRV_LDO_EN;
	tx_ana_ctrl_reg_1 &= ~TXDA_BGREF_EN;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
	udelay(1);
	tx_ana_ctrl_reg_1 |= TXDA_DECAP_EN_DEL;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);

	/*
	 * Undo the work we did to set the LDO voltage.
	 * This doesn't seem to help nor hurt, but it kinda goes with the
	 * undocumented magic above.
	 */
	writel(0, tcphy->base + TX_ANA_CTRL_REG_4);

	/* Don't set voltage swing to 400 mV peak to peak (differential) */
	writel(0, tcphy->base + TXDA_COEFF_CALC_CTRL);

	/* Init TXDA_CYA_AUXDA_CYA for unknown magic reasons */
	writel(0, tcphy->base + TXDA_CYA_AUXDA_CYA);

	/*
	 * More undocumented magic, presumably the goal of which is to
	 * make the "auxda_source_aux_oen" be ignored and instead to decide
	 * about "high impedance state" based on what software puts in the
	 * register TXDA_COEFF_CALC_CTRL (see TX_HIGH_Z).  Since we only
	 * program that register once and we don't set the bit TX_HIGH_Z,
	 * presumably the goal here is that we should never put the analog
	 * driver in high impedance state.
	 */
	val = readl(tcphy->base + TX_DIG_CTRL_REG_2);
	val |= TX_HIGH_Z_TM_EN;
	writel(val, tcphy->base + TX_DIG_CTRL_REG_2);
}