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
struct xvcu_pll_cfg {int fbdiv; int res; int cp; int lfhf; int lock_cnt; int lock_dly; } ;
struct xvcu_device {int coreclk; int /*<<< orphan*/  vcu_slcr_ba; int /*<<< orphan*/  dev; int /*<<< orphan*/  pll_ref; int /*<<< orphan*/  logicore_reg_ba; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct xvcu_pll_cfg*) ; 
 int DIVISOR_MAX ; 
 int DIVISOR_MIN ; 
 int EINVAL ; 
 int FRAC ; 
 int FVCO_MAX ; 
 int FVCO_MIN ; 
 int LIMIT ; 
 int MHZ ; 
 int /*<<< orphan*/  VCU_CORE_CLK ; 
 int /*<<< orphan*/  VCU_DEC_CORE_CTRL ; 
 int /*<<< orphan*/  VCU_DEC_MCU_CTRL ; 
 int /*<<< orphan*/  VCU_ENC_CORE_CTRL ; 
 int /*<<< orphan*/  VCU_ENC_MCU_CTRL ; 
 int /*<<< orphan*/  VCU_MCU_CLK ; 
 int /*<<< orphan*/  VCU_PLL_CFG ; 
 int VCU_PLL_CFG_CP_SHIFT ; 
 int VCU_PLL_CFG_LFHF_SHIFT ; 
 int VCU_PLL_CFG_LOCK_CNT_SHIFT ; 
 int VCU_PLL_CFG_LOCK_DLY_SHIFT ; 
 int VCU_PLL_CFG_RES_SHIFT ; 
 int /*<<< orphan*/  VCU_PLL_CLK ; 
 int /*<<< orphan*/  VCU_PLL_CLK_DEC ; 
 int /*<<< orphan*/  VCU_PLL_CTRL ; 
 int VCU_PLL_CTRL_CLKOUTDIV_MASK ; 
 int VCU_PLL_CTRL_CLKOUTDIV_SHIFT ; 
 int VCU_PLL_CTRL_DEFAULT ; 
 int VCU_PLL_CTRL_FBDIV_MASK ; 
 int VCU_PLL_CTRL_FBDIV_SHIFT ; 
 int VCU_PLL_CTRL_POR_IN_MASK ; 
 int VCU_PLL_CTRL_POR_IN_SHIFT ; 
 int VCU_PLL_CTRL_PWR_POR_MASK ; 
 int VCU_PLL_CTRL_PWR_POR_SHIFT ; 
 int VCU_PLL_DIV2 ; 
 int VCU_PLL_DIVISOR_MASK ; 
 int VCU_PLL_DIVISOR_SHIFT ; 
 int VCU_SRCSEL_MASK ; 
 int VCU_SRCSEL_PLL ; 
 int VCU_SRCSEL_SHIFT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct xvcu_pll_cfg* xvcu_pll_cfg ; 
 int xvcu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xvcu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xvcu_set_vcu_pll_info(struct xvcu_device *xvcu)
{
	u32 refclk, coreclk, mcuclk, inte, deci;
	u32 divisor_mcu, divisor_core, fvco;
	u32 clkoutdiv, vcu_pll_ctrl, pll_clk;
	u32 cfg_val, mod, ctrl;
	int ret, i;
	const struct xvcu_pll_cfg *found = NULL;

	inte = xvcu_read(xvcu->logicore_reg_ba, VCU_PLL_CLK);
	deci = xvcu_read(xvcu->logicore_reg_ba, VCU_PLL_CLK_DEC);
	coreclk = xvcu_read(xvcu->logicore_reg_ba, VCU_CORE_CLK) * MHZ;
	mcuclk = xvcu_read(xvcu->logicore_reg_ba, VCU_MCU_CLK) * MHZ;
	if (!mcuclk || !coreclk) {
		dev_err(xvcu->dev, "Invalid mcu and core clock data\n");
		return -EINVAL;
	}

	refclk = (inte * MHZ) + (deci * (MHZ / FRAC));
	dev_dbg(xvcu->dev, "Ref clock from logicoreIP is %uHz\n", refclk);
	dev_dbg(xvcu->dev, "Core clock from logicoreIP is %uHz\n", coreclk);
	dev_dbg(xvcu->dev, "Mcu clock from logicoreIP is %uHz\n", mcuclk);

	clk_disable_unprepare(xvcu->pll_ref);
	ret = clk_set_rate(xvcu->pll_ref, refclk);
	if (ret)
		dev_warn(xvcu->dev, "failed to set logicoreIP refclk rate\n");

	ret = clk_prepare_enable(xvcu->pll_ref);
	if (ret) {
		dev_err(xvcu->dev, "failed to enable pll_ref clock source\n");
		return ret;
	}

	refclk = clk_get_rate(xvcu->pll_ref);

	/*
	 * The divide-by-2 should be always enabled (==1)
	 * to meet the timing in the design.
	 * Otherwise, it's an error
	 */
	vcu_pll_ctrl = xvcu_read(xvcu->vcu_slcr_ba, VCU_PLL_CTRL);
	clkoutdiv = vcu_pll_ctrl >> VCU_PLL_CTRL_CLKOUTDIV_SHIFT;
	clkoutdiv = clkoutdiv & VCU_PLL_CTRL_CLKOUTDIV_MASK;
	if (clkoutdiv != 1) {
		dev_err(xvcu->dev, "clkoutdiv value is invalid\n");
		return -EINVAL;
	}

	for (i = ARRAY_SIZE(xvcu_pll_cfg) - 1; i >= 0; i--) {
		const struct xvcu_pll_cfg *cfg = &xvcu_pll_cfg[i];

		fvco = cfg->fbdiv * refclk;
		if (fvco >= FVCO_MIN && fvco <= FVCO_MAX) {
			pll_clk = fvco / VCU_PLL_DIV2;
			if (fvco % VCU_PLL_DIV2 != 0)
				pll_clk++;
			mod = pll_clk % coreclk;
			if (mod < LIMIT) {
				divisor_core = pll_clk / coreclk;
			} else if (coreclk - mod < LIMIT) {
				divisor_core = pll_clk / coreclk;
				divisor_core++;
			} else {
				continue;
			}
			if (divisor_core >= DIVISOR_MIN &&
			    divisor_core <= DIVISOR_MAX) {
				found = cfg;
				divisor_mcu = pll_clk / mcuclk;
				mod = pll_clk % mcuclk;
				if (mcuclk - mod < LIMIT)
					divisor_mcu++;
				break;
			}
		}
	}

	if (!found) {
		dev_err(xvcu->dev, "Invalid clock combination.\n");
		return -EINVAL;
	}

	xvcu->coreclk = pll_clk / divisor_core;
	mcuclk = pll_clk / divisor_mcu;
	dev_dbg(xvcu->dev, "Actual Ref clock freq is %uHz\n", refclk);
	dev_dbg(xvcu->dev, "Actual Core clock freq is %uHz\n", xvcu->coreclk);
	dev_dbg(xvcu->dev, "Actual Mcu clock freq is %uHz\n", mcuclk);

	vcu_pll_ctrl &= ~(VCU_PLL_CTRL_FBDIV_MASK << VCU_PLL_CTRL_FBDIV_SHIFT);
	vcu_pll_ctrl |= (found->fbdiv & VCU_PLL_CTRL_FBDIV_MASK) <<
			 VCU_PLL_CTRL_FBDIV_SHIFT;
	vcu_pll_ctrl &= ~(VCU_PLL_CTRL_POR_IN_MASK <<
			  VCU_PLL_CTRL_POR_IN_SHIFT);
	vcu_pll_ctrl |= (VCU_PLL_CTRL_DEFAULT & VCU_PLL_CTRL_POR_IN_MASK) <<
			 VCU_PLL_CTRL_POR_IN_SHIFT;
	vcu_pll_ctrl &= ~(VCU_PLL_CTRL_PWR_POR_MASK <<
			  VCU_PLL_CTRL_PWR_POR_SHIFT);
	vcu_pll_ctrl |= (VCU_PLL_CTRL_DEFAULT & VCU_PLL_CTRL_PWR_POR_MASK) <<
			 VCU_PLL_CTRL_PWR_POR_SHIFT;
	xvcu_write(xvcu->vcu_slcr_ba, VCU_PLL_CTRL, vcu_pll_ctrl);

	/* Set divisor for the core and mcu clock */
	ctrl = xvcu_read(xvcu->vcu_slcr_ba, VCU_ENC_CORE_CTRL);
	ctrl &= ~(VCU_PLL_DIVISOR_MASK << VCU_PLL_DIVISOR_SHIFT);
	ctrl |= (divisor_core & VCU_PLL_DIVISOR_MASK) <<
		 VCU_PLL_DIVISOR_SHIFT;
	ctrl &= ~(VCU_SRCSEL_MASK << VCU_SRCSEL_SHIFT);
	ctrl |= (VCU_SRCSEL_PLL & VCU_SRCSEL_MASK) << VCU_SRCSEL_SHIFT;
	xvcu_write(xvcu->vcu_slcr_ba, VCU_ENC_CORE_CTRL, ctrl);

	ctrl = xvcu_read(xvcu->vcu_slcr_ba, VCU_DEC_CORE_CTRL);
	ctrl &= ~(VCU_PLL_DIVISOR_MASK << VCU_PLL_DIVISOR_SHIFT);
	ctrl |= (divisor_core & VCU_PLL_DIVISOR_MASK) <<
		 VCU_PLL_DIVISOR_SHIFT;
	ctrl &= ~(VCU_SRCSEL_MASK << VCU_SRCSEL_SHIFT);
	ctrl |= (VCU_SRCSEL_PLL & VCU_SRCSEL_MASK) << VCU_SRCSEL_SHIFT;
	xvcu_write(xvcu->vcu_slcr_ba, VCU_DEC_CORE_CTRL, ctrl);

	ctrl = xvcu_read(xvcu->vcu_slcr_ba, VCU_ENC_MCU_CTRL);
	ctrl &= ~(VCU_PLL_DIVISOR_MASK << VCU_PLL_DIVISOR_SHIFT);
	ctrl |= (divisor_mcu & VCU_PLL_DIVISOR_MASK) << VCU_PLL_DIVISOR_SHIFT;
	ctrl &= ~(VCU_SRCSEL_MASK << VCU_SRCSEL_SHIFT);
	ctrl |= (VCU_SRCSEL_PLL & VCU_SRCSEL_MASK) << VCU_SRCSEL_SHIFT;
	xvcu_write(xvcu->vcu_slcr_ba, VCU_ENC_MCU_CTRL, ctrl);

	ctrl = xvcu_read(xvcu->vcu_slcr_ba, VCU_DEC_MCU_CTRL);
	ctrl &= ~(VCU_PLL_DIVISOR_MASK << VCU_PLL_DIVISOR_SHIFT);
	ctrl |= (divisor_mcu & VCU_PLL_DIVISOR_MASK) << VCU_PLL_DIVISOR_SHIFT;
	ctrl &= ~(VCU_SRCSEL_MASK << VCU_SRCSEL_SHIFT);
	ctrl |= (VCU_SRCSEL_PLL & VCU_SRCSEL_MASK) << VCU_SRCSEL_SHIFT;
	xvcu_write(xvcu->vcu_slcr_ba, VCU_DEC_MCU_CTRL, ctrl);

	/* Set RES, CP, LFHF, LOCK_CNT and LOCK_DLY cfg values */
	cfg_val = (found->res << VCU_PLL_CFG_RES_SHIFT) |
		   (found->cp << VCU_PLL_CFG_CP_SHIFT) |
		   (found->lfhf << VCU_PLL_CFG_LFHF_SHIFT) |
		   (found->lock_cnt << VCU_PLL_CFG_LOCK_CNT_SHIFT) |
		   (found->lock_dly << VCU_PLL_CFG_LOCK_DLY_SHIFT);
	xvcu_write(xvcu->vcu_slcr_ba, VCU_PLL_CFG, cfg_val);

	return 0;
}