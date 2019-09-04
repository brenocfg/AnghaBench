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
struct hdmi_pll_8996 {int dummy; } ;
struct hdmi_phy {int dummy; } ;
struct hdmi_8996_phy_pll_reg_cfg {int* tx_lx_tx_band; int* tx_lx_lane_mode; int com_svs_mode_clk_sel; int com_vco_tune_ctrl; int com_hsclk_sel; int com_lock_cmp_en; int com_pll_cctrl_mode0; int com_pll_rctrl_mode0; int com_cp_ctrl_mode0; int com_dec_start_mode0; int com_div_frac_start1_mode0; int com_div_frac_start2_mode0; int com_div_frac_start3_mode0; int com_integloop_gain0_mode0; int com_integloop_gain1_mode0; int com_lock_cmp1_mode0; int com_lock_cmp2_mode0; int com_lock_cmp3_mode0; int com_core_clk_en; int com_coreclk_div; int* tx_lx_tx_drv_lvl; int* tx_lx_tx_emp_post1_lvl; int* tx_lx_vmode_ctrl1; int* tx_lx_vmode_ctrl2; int* tx_lx_hp_pd_enables; int phy_mode; } ;
struct clk_hw {int dummy; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HDMI_NUM_TX_CHANNEL ; 
 int /*<<< orphan*/  REG_HDMI_8996_PHY_MODE ; 
 int /*<<< orphan*/  REG_HDMI_8996_PHY_PD_CTL ; 
 int /*<<< orphan*/  REG_HDMI_8996_PHY_TX0_TX1_LANE_CTL ; 
 int /*<<< orphan*/  REG_HDMI_8996_PHY_TX2_TX3_LANE_CTL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_BG_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_BG_TRIM ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_BIAS_EN_CLKBUFLR_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CLK_ENABLE1 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CLK_SELECT ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CMN_CONFIG ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CORECLK_DIV ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CORE_CLK_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_CP_CTRL_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_DEC_START_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START1_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START2_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START3_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_HSCLK_SEL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN0_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN1_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_LOCK_CMP_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_PLL_CCTRL_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_PLL_IVCO ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_PLL_RCTRL_MODE0 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_RESCODE_DIV_NUM ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_RESETSM_CNTRL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_SVS_MODE_CLK_SEL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_SYSCLK_BUF_ENABLE ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_SYSCLK_EN_SEL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_SYS_CLK_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_MAP ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_CLKBUF_ENABLE ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_HP_PD_ENABLES ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_LANE_MODE ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_PARRATE_REC_DETECT_IDLE_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_RESET_TSYNC_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_RES_CODE_LANE_OFFSET ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_TRAN_DRVR_EMP_EN ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_TX_BAND ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL_OFFSET ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_TX_EMP_POST1_LVL ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL1 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL2 ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_pll_write (struct hdmi_pll_8996*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_tx_chan_write (struct hdmi_pll_8996*,int,int /*<<< orphan*/ ,int) ; 
 struct hdmi_pll_8996* hw_clk_to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  memset (struct hdmi_8996_phy_pll_reg_cfg*,int,int) ; 
 int pll_calculate (unsigned long,unsigned long,struct hdmi_8996_phy_pll_reg_cfg*) ; 
 struct hdmi_phy* pll_get_phy (struct hdmi_pll_8996*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hdmi_8996_pll_set_clk_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long parent_rate)
{
	struct hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	struct hdmi_phy *phy = pll_get_phy(pll);
	struct hdmi_8996_phy_pll_reg_cfg cfg;
	int i, ret;

	memset(&cfg, 0x00, sizeof(cfg));

	ret = pll_calculate(rate, parent_rate, &cfg);
	if (ret) {
		DRM_ERROR("PLL calculation failed\n");
		return ret;
	}

	/* Initially shut down PHY */
	DBG("Disabling PHY");
	hdmi_phy_write(phy, REG_HDMI_8996_PHY_PD_CTL, 0x0);
	udelay(500);

	/* Power up sequence */
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_BG_CTRL, 0x04);

	hdmi_phy_write(phy, REG_HDMI_8996_PHY_PD_CTL, 0x1);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_RESETSM_CNTRL, 0x20);
	hdmi_phy_write(phy, REG_HDMI_8996_PHY_TX0_TX1_LANE_CTL, 0x0F);
	hdmi_phy_write(phy, REG_HDMI_8996_PHY_TX2_TX3_LANE_CTL, 0x0F);

	for (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) {
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_CLKBUF_ENABLE,
				   0x03);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_BAND,
				   cfg.tx_lx_tx_band[i]);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_RESET_TSYNC_EN,
				   0x03);
	}

	hdmi_tx_chan_write(pll, 0, REG_HDMI_PHY_QSERDES_TX_LX_LANE_MODE,
			   cfg.tx_lx_lane_mode[0]);
	hdmi_tx_chan_write(pll, 2, REG_HDMI_PHY_QSERDES_TX_LX_LANE_MODE,
			   cfg.tx_lx_lane_mode[2]);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_SYSCLK_BUF_ENABLE, 0x1E);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_BIAS_EN_CLKBUFLR_EN, 0x07);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_SYSCLK_EN_SEL, 0x37);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_SYS_CLK_CTRL, 0x02);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CLK_ENABLE1, 0x0E);

	/* Bypass VCO calibration */
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_SVS_MODE_CLK_SEL,
		       cfg.com_svs_mode_clk_sel);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_BG_TRIM, 0x0F);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_PLL_IVCO, 0x0F);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_CTRL,
		       cfg.com_vco_tune_ctrl);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_BG_CTRL, 0x06);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CLK_SELECT, 0x30);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_HSCLK_SEL,
		       cfg.com_hsclk_sel);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP_EN,
		       cfg.com_lock_cmp_en);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_PLL_CCTRL_MODE0,
		       cfg.com_pll_cctrl_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_PLL_RCTRL_MODE0,
		       cfg.com_pll_rctrl_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CP_CTRL_MODE0,
		       cfg.com_cp_ctrl_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_DEC_START_MODE0,
		       cfg.com_dec_start_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START1_MODE0,
		       cfg.com_div_frac_start1_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START2_MODE0,
		       cfg.com_div_frac_start2_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START3_MODE0,
		       cfg.com_div_frac_start3_mode0);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN0_MODE0,
		       cfg.com_integloop_gain0_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN1_MODE0,
		       cfg.com_integloop_gain1_mode0);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0,
		       cfg.com_lock_cmp1_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0,
		       cfg.com_lock_cmp2_mode0);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0,
		       cfg.com_lock_cmp3_mode0);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_MAP, 0x00);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CORE_CLK_EN,
		       cfg.com_core_clk_en);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CORECLK_DIV,
		       cfg.com_coreclk_div);
	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_CMN_CONFIG, 0x02);

	hdmi_pll_write(pll, REG_HDMI_PHY_QSERDES_COM_RESCODE_DIV_NUM, 0x15);

	/* TX lanes setup (TX 0/1/2/3) */
	for (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) {
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL,
				   cfg.tx_lx_tx_drv_lvl[i]);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_EMP_POST1_LVL,
				   cfg.tx_lx_tx_emp_post1_lvl[i]);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL1,
				   cfg.tx_lx_vmode_ctrl1[i]);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL2,
				   cfg.tx_lx_vmode_ctrl2[i]);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL_OFFSET,
				   0x00);
		hdmi_tx_chan_write(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_RES_CODE_LANE_OFFSET,
			0x00);
		hdmi_tx_chan_write(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_TRAN_DRVR_EMP_EN,
			0x03);
		hdmi_tx_chan_write(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_PARRATE_REC_DETECT_IDLE_EN,
			0x40);
		hdmi_tx_chan_write(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_HP_PD_ENABLES,
				   cfg.tx_lx_hp_pd_enables[i]);
	}

	hdmi_phy_write(phy, REG_HDMI_8996_PHY_MODE, cfg.phy_mode);
	hdmi_phy_write(phy, REG_HDMI_8996_PHY_PD_CTL, 0x1F);

	/*
	 * Ensure that vco configuration gets flushed to hardware before
	 * enabling the PLL
	 */
	wmb();

	return 0;
}