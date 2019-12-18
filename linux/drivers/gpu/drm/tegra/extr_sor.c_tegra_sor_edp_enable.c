#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct tegra_sor_state {int bpc; } ;
struct tegra_sor_config {int bits_per_pixel; } ;
struct tegra_sor {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; TYPE_4__* soc; int /*<<< orphan*/  clk_dp; int /*<<< orphan*/ * xbar_cfg; int /*<<< orphan*/  pad; int /*<<< orphan*/  clk_safe; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct tegra_output {scalar_t__ panel; TYPE_2__ connector; } ;
struct tegra_dc {int dummy; } ;
struct drm_encoder {TYPE_5__* crtc; } ;
struct drm_dp_link {int num_lanes; int capabilities; int /*<<< orphan*/  rate; } ;
struct drm_display_mode {int dummy; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_10__ {TYPE_1__* state; } ;
struct TYPE_9__ {TYPE_3__* regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  dp_padctl0; int /*<<< orphan*/  pll2; int /*<<< orphan*/  pll0; int /*<<< orphan*/  pll1; int /*<<< orphan*/  pll3; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int DP_LINK_CAP_ENHANCED_FRAMING ; 
 int /*<<< orphan*/  SOR_CLK_CNTRL ; 
 int SOR_CLK_CNTRL_DP_CLK_SEL_MASK ; 
 int SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED (int) ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED_G1_62 ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  SOR_CSTM ; 
 int SOR_CSTM_LINK_ACT_A ; 
 int SOR_CSTM_LINK_ACT_B ; 
 int SOR_CSTM_LVDS ; 
 int SOR_CSTM_UPPER ; 
 int /*<<< orphan*/  SOR_DP_LINKCTL0 ; 
 int SOR_DP_LINKCTL_ENABLE ; 
 int SOR_DP_LINKCTL_ENHANCED_FRAME ; 
 int SOR_DP_LINKCTL_LANE_COUNT (int) ; 
 int SOR_DP_LINKCTL_LANE_COUNT_MASK ; 
 int SOR_DP_PADCTL_PAD_CAL_PD ; 
 int SOR_DP_PADCTL_PD_TXD_0 ; 
 int SOR_DP_PADCTL_PD_TXD_1 ; 
 int SOR_DP_PADCTL_PD_TXD_2 ; 
 int SOR_DP_PADCTL_PD_TXD_3 ; 
 int /*<<< orphan*/  SOR_DP_TPG ; 
 unsigned long SOR_DP_TPG_CHANNEL_CODING ; 
 unsigned long SOR_DP_TPG_PATTERN_NONE ; 
 unsigned long SOR_DP_TPG_SCRAMBLER_GALIOS ; 
 int SOR_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOR_LANE_SEQ_CTL ; 
 int SOR_LANE_SEQ_CTL_POWER_STATE_UP ; 
 int SOR_LANE_SEQ_CTL_SEQUENCE_DOWN ; 
 int SOR_LANE_SEQ_CTL_TRIGGER ; 
 int SOR_PLL0_ICHPMP (int) ; 
 int SOR_PLL0_PLLREG_LEVEL_V45 ; 
 int SOR_PLL0_PWR ; 
 int SOR_PLL0_RESISTOR_EXT ; 
 int SOR_PLL0_VCOCAP_RST ; 
 int SOR_PLL0_VCOPD ; 
 int SOR_PLL1_TERM_COMPOUT ; 
 int SOR_PLL1_TMDS_TERM ; 
 int SOR_PLL2_BANDGAP_POWERDOWN ; 
 int SOR_PLL2_LVDS_ENABLE ; 
 int SOR_PLL2_PORT_POWERDOWN ; 
 int SOR_PLL2_POWERDOWN_OVERRIDE ; 
 int SOR_PLL2_SEQ_PLLCAPPD ; 
 int SOR_PLL2_SEQ_PLLCAPPD_ENFORCE ; 
 int SOR_PLL3_PLL_VDD_MODE_3V3 ; 
 int /*<<< orphan*/  SOR_STATE1 ; 
 int SOR_STATE_ASY_PROTOCOL_DP_A ; 
 int SOR_STATE_ASY_PROTOCOL_MASK ; 
 int /*<<< orphan*/  SOR_XBAR_CTRL ; 
 int SOR_XBAR_CTRL_LINK0_XSEL (unsigned int,int /*<<< orphan*/ ) ; 
 int SOR_XBAR_CTRL_LINK1_XSEL (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  SOR_XBAR_POL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_dp_aux_enable (int /*<<< orphan*/ ) ; 
 int drm_dp_link_configure (int /*<<< orphan*/ ,struct drm_dp_link*) ; 
 int drm_dp_link_power_up (int /*<<< orphan*/ ,struct drm_dp_link*) ; 
 int drm_dp_link_probe (int /*<<< orphan*/ ,struct drm_dp_link*) ; 
 int drm_dp_link_rate_to_bw_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  memset (struct tegra_sor_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 
 int tegra_io_pad_power_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_apply_config (struct tegra_sor*,struct tegra_sor_config*) ; 
 int tegra_sor_attach (struct tegra_sor*) ; 
 int tegra_sor_compute_config (struct tegra_sor*,struct drm_display_mode*,struct tegra_sor_config*,struct drm_dp_link*) ; 
 int tegra_sor_dp_train_fast (struct tegra_sor*,struct drm_dp_link*) ; 
 int /*<<< orphan*/  tegra_sor_mode_set (struct tegra_sor*,struct drm_display_mode*,struct tegra_sor_state*) ; 
 int tegra_sor_power_up (struct tegra_sor*,int) ; 
 int tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int tegra_sor_set_parent_clock (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int tegra_sor_setup_pwm (struct tegra_sor*,int) ; 
 int /*<<< orphan*/  tegra_sor_update (struct tegra_sor*) ; 
 int tegra_sor_wakeup (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,int /*<<< orphan*/ ) ; 
 struct tegra_sor* to_sor (struct tegra_output*) ; 
 struct tegra_sor_state* to_sor_state (int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (TYPE_5__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tegra_sor_edp_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dc *dc = to_tegra_dc(encoder->crtc);
	struct tegra_sor *sor = to_sor(output);
	struct tegra_sor_config config;
	struct tegra_sor_state *state;
	struct drm_dp_link link;
	u8 rate, lanes;
	unsigned int i;
	int err = 0;
	u32 value;

	state = to_sor_state(output->connector.state);

	pm_runtime_get_sync(sor->dev);

	if (output->panel)
		drm_panel_prepare(output->panel);

	err = drm_dp_aux_enable(sor->aux);
	if (err < 0)
		dev_err(sor->dev, "failed to enable DP: %d\n", err);

	err = drm_dp_link_probe(sor->aux, &link);
	if (err < 0) {
		dev_err(sor->dev, "failed to probe eDP link: %d\n", err);
		return;
	}

	/* switch to safe parent clock */
	err = tegra_sor_set_parent_clock(sor, sor->clk_safe);
	if (err < 0)
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);

	memset(&config, 0, sizeof(config));
	config.bits_per_pixel = state->bpc * 3;

	err = tegra_sor_compute_config(sor, mode, &config, &link);
	if (err < 0)
		dev_err(sor->dev, "failed to compute configuration: %d\n", err);

	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;
	value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK;
	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);
	usleep_range(20, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->pll3);
	value |= SOR_PLL3_PLL_VDD_MODE_3V3;
	tegra_sor_writel(sor, value, sor->soc->regs->pll3);

	value = SOR_PLL0_ICHPMP(0xf) | SOR_PLL0_VCOCAP_RST |
		SOR_PLL0_PLLREG_LEVEL_V45 | SOR_PLL0_RESISTOR_EXT;
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_SEQ_PLLCAPPD;
	value &= ~SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	value |= SOR_PLL2_LVDS_ENABLE;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	value = SOR_PLL1_TERM_COMPOUT | SOR_PLL1_TMDS_TERM;
	tegra_sor_writel(sor, value, sor->soc->regs->pll1);

	while (true) {
		value = tegra_sor_readl(sor, sor->soc->regs->pll2);
		if ((value & SOR_PLL2_SEQ_PLLCAPPD_ENFORCE) == 0)
			break;

		usleep_range(250, 1000);
	}

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_POWERDOWN_OVERRIDE;
	value &= ~SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	/*
	 * power up
	 */

	/* set safe link bandwidth (1.62 Gbps) */
	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value |= SOR_CLK_CNTRL_DP_LINK_SPEED_G1_62;
	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	/* step 1 */
	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value |= SOR_PLL2_SEQ_PLLCAPPD_ENFORCE | SOR_PLL2_PORT_POWERDOWN |
		 SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	value = tegra_sor_readl(sor, sor->soc->regs->pll0);
	value |= SOR_PLL0_VCOPD | SOR_PLL0_PWR;
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	/* step 2 */
	err = tegra_io_pad_power_enable(sor->pad);
	if (err < 0)
		dev_err(sor->dev, "failed to power on I/O pad: %d\n", err);

	usleep_range(5, 100);

	/* step 3 */
	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	/* step 4 */
	value = tegra_sor_readl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_VCOPD;
	value &= ~SOR_PLL0_PWR;
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(200, 1000);

	/* step 5 */
	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	/* XXX not in TRM */
	for (value = 0, i = 0; i < 5; i++)
		value |= SOR_XBAR_CTRL_LINK0_XSEL(i, sor->xbar_cfg[i]) |
			 SOR_XBAR_CTRL_LINK1_XSEL(i, i);

	tegra_sor_writel(sor, 0x00000000, SOR_XBAR_POL);
	tegra_sor_writel(sor, value, SOR_XBAR_CTRL);

	/* switch to DP parent clock */
	err = tegra_sor_set_parent_clock(sor, sor->clk_dp);
	if (err < 0)
		dev_err(sor->dev, "failed to set parent clock: %d\n", err);

	/* power DP lanes */
	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);

	if (link.num_lanes <= 2)
		value &= ~(SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_2);
	else
		value |= SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_2;

	if (link.num_lanes <= 1)
		value &= ~SOR_DP_PADCTL_PD_TXD_1;
	else
		value |= SOR_DP_PADCTL_PD_TXD_1;

	if (link.num_lanes == 0)
		value &= ~SOR_DP_PADCTL_PD_TXD_0;
	else
		value |= SOR_DP_PADCTL_PD_TXD_0;

	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	value = tegra_sor_readl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_LANE_COUNT_MASK;
	value |= SOR_DP_LINKCTL_LANE_COUNT(link.num_lanes);
	tegra_sor_writel(sor, value, SOR_DP_LINKCTL0);

	/* start lane sequencer */
	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_DOWN |
		SOR_LANE_SEQ_CTL_POWER_STATE_UP;
	tegra_sor_writel(sor, value, SOR_LANE_SEQ_CTL);

	while (true) {
		value = tegra_sor_readl(sor, SOR_LANE_SEQ_CTL);
		if ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			break;

		usleep_range(250, 1000);
	}

	/* set link bandwidth */
	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value |= drm_dp_link_rate_to_bw_code(link.rate) << 2;
	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	tegra_sor_apply_config(sor, &config);

	/* enable link */
	value = tegra_sor_readl(sor, SOR_DP_LINKCTL0);
	value |= SOR_DP_LINKCTL_ENABLE;
	value |= SOR_DP_LINKCTL_ENHANCED_FRAME;
	tegra_sor_writel(sor, value, SOR_DP_LINKCTL0);

	for (i = 0, value = 0; i < 4; i++) {
		unsigned long lane = SOR_DP_TPG_CHANNEL_CODING |
				     SOR_DP_TPG_SCRAMBLER_GALIOS |
				     SOR_DP_TPG_PATTERN_NONE;
		value = (value << 8) | lane;
	}

	tegra_sor_writel(sor, value, SOR_DP_TPG);

	/* enable pad calibration logic */
	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	err = drm_dp_link_probe(sor->aux, &link);
	if (err < 0)
		dev_err(sor->dev, "failed to probe eDP link: %d\n", err);

	err = drm_dp_link_power_up(sor->aux, &link);
	if (err < 0)
		dev_err(sor->dev, "failed to power up eDP link: %d\n", err);

	err = drm_dp_link_configure(sor->aux, &link);
	if (err < 0)
		dev_err(sor->dev, "failed to configure eDP link: %d\n", err);

	rate = drm_dp_link_rate_to_bw_code(link.rate);
	lanes = link.num_lanes;

	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value |= SOR_CLK_CNTRL_DP_LINK_SPEED(rate);
	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	value = tegra_sor_readl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_LANE_COUNT_MASK;
	value |= SOR_DP_LINKCTL_LANE_COUNT(lanes);

	if (link.capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
		value |= SOR_DP_LINKCTL_ENHANCED_FRAME;

	tegra_sor_writel(sor, value, SOR_DP_LINKCTL0);

	/* disable training pattern generator */

	for (i = 0; i < link.num_lanes; i++) {
		unsigned long lane = SOR_DP_TPG_CHANNEL_CODING |
				     SOR_DP_TPG_SCRAMBLER_GALIOS |
				     SOR_DP_TPG_PATTERN_NONE;
		value = (value << 8) | lane;
	}

	tegra_sor_writel(sor, value, SOR_DP_TPG);

	err = tegra_sor_dp_train_fast(sor, &link);
	if (err < 0)
		dev_err(sor->dev, "DP fast link training failed: %d\n", err);

	dev_dbg(sor->dev, "fast link training succeeded\n");

	err = tegra_sor_power_up(sor, 250);
	if (err < 0)
		dev_err(sor->dev, "failed to power up SOR: %d\n", err);

	/* CSTM (LVDS, link A/B, upper) */
	value = SOR_CSTM_LVDS | SOR_CSTM_LINK_ACT_A | SOR_CSTM_LINK_ACT_B |
		SOR_CSTM_UPPER;
	tegra_sor_writel(sor, value, SOR_CSTM);

	/* use DP-A protocol */
	value = tegra_sor_readl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PROTOCOL_MASK;
	value |= SOR_STATE_ASY_PROTOCOL_DP_A;
	tegra_sor_writel(sor, value, SOR_STATE1);

	tegra_sor_mode_set(sor, mode, state);

	/* PWM setup */
	err = tegra_sor_setup_pwm(sor, 250);
	if (err < 0)
		dev_err(sor->dev, "failed to setup PWM: %d\n", err);

	tegra_sor_update(sor);

	value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= SOR_ENABLE(0);
	tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	err = tegra_sor_attach(sor);
	if (err < 0)
		dev_err(sor->dev, "failed to attach SOR: %d\n", err);

	err = tegra_sor_wakeup(sor);
	if (err < 0)
		dev_err(sor->dev, "failed to enable DC: %d\n", err);

	if (output->panel)
		drm_panel_enable(output->panel);
}