#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_sor_state {int bpc; } ;
struct tegra_sor_hdmi_settings {int* drive_current; int* preemphasis; int /*<<< orphan*/  sparepll; int /*<<< orphan*/  tx_pu_value; int /*<<< orphan*/  avdd14_level; int /*<<< orphan*/  avdd10_level; int /*<<< orphan*/  bg_vref_level; int /*<<< orphan*/  bg_temp_coef; int /*<<< orphan*/  tmds_termadj; int /*<<< orphan*/  loadadj; int /*<<< orphan*/  vcocap; int /*<<< orphan*/  filter; int /*<<< orphan*/  ichpmp; } ;
struct tegra_sor {int index; int /*<<< orphan*/  dev; TYPE_4__* soc; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk_pad; int /*<<< orphan*/ * xbar_cfg; int /*<<< orphan*/  pad; int /*<<< orphan*/  clk_safe; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct tegra_output {TYPE_1__ connector; } ;
struct tegra_dc {TYPE_5__* soc; scalar_t__ pipe; } ;
struct drm_encoder {TYPE_6__* crtc; } ;
struct drm_display_mode {int clock; int htotal; int hdisplay; unsigned int hsync_end; unsigned int hsync_start; } ;
struct TYPE_12__ {TYPE_2__* state; } ;
struct TYPE_11__ {scalar_t__ has_nvdisplay; } ;
struct TYPE_10__ {int /*<<< orphan*/  has_nvdisplay; TYPE_3__* regs; } ;
struct TYPE_9__ {scalar_t__ head_state0; scalar_t__ dp_padctl0; scalar_t__ dp_padctl2; scalar_t__ pll3; scalar_t__ pll1; scalar_t__ pll0; scalar_t__ pll2; } ;
struct TYPE_8__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int BASE_COLOR_SIZE_101010 ; 
 int BASE_COLOR_SIZE_121212 ; 
 int BASE_COLOR_SIZE_666 ; 
 int BASE_COLOR_SIZE_888 ; 
 int BASE_COLOR_SIZE_MASK ; 
 int /*<<< orphan*/  DC_DISP_CORE_SOR_SET_CONTROL (int) ; 
 int /*<<< orphan*/  DC_DISP_DISP_COLOR_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_DISP_SIGNAL_OPTIONS0 ; 
 int /*<<< orphan*/  DC_DISP_DISP_TIMING_OPTIONS ; 
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int /*<<< orphan*/  DC_DISP_H_PULSE2_CONTROL ; 
 int /*<<< orphan*/  DC_DISP_H_PULSE2_POSITION_A ; 
 int DITHER_CONTROL_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int H_PULSE2_ENABLE ; 
 int PROTOCOL_MASK ; 
 int PROTOCOL_SINGLE_TMDS_A ; 
 int PULSE_END (unsigned int) ; 
 int PULSE_LAST_END_A ; 
 int PULSE_MODE_NORMAL ; 
 int PULSE_POLARITY_HIGH ; 
 int PULSE_QUAL_VACTIVE ; 
 int PULSE_START (unsigned int) ; 
 int SOR1_TIMING_CYA ; 
 scalar_t__ SOR_CLK_CNTRL ; 
 int SOR_CLK_CNTRL_DP_CLK_SEL_MASK ; 
 int SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED_G2_70 ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED_G5_40 ; 
 int SOR_CLK_CNTRL_DP_LINK_SPEED_MASK ; 
 scalar_t__ SOR_DP_LINKCTL0 ; 
 int SOR_DP_LINKCTL_LANE_COUNT (int) ; 
 int SOR_DP_LINKCTL_LANE_COUNT_MASK ; 
 int SOR_DP_PADCTL_PAD_CAL_PD ; 
 int SOR_DP_PADCTL_PD_TXD_0 ; 
 int SOR_DP_PADCTL_PD_TXD_1 ; 
 int SOR_DP_PADCTL_PD_TXD_2 ; 
 int SOR_DP_PADCTL_PD_TXD_3 ; 
 int SOR_DP_PADCTL_SPAREPLL (int /*<<< orphan*/ ) ; 
 int SOR_DP_PADCTL_SPAREPLL_MASK ; 
 int SOR_DP_PADCTL_TX_PU (int /*<<< orphan*/ ) ; 
 int SOR_DP_PADCTL_TX_PU_ENABLE ; 
 int SOR_DP_PADCTL_TX_PU_MASK ; 
 scalar_t__ SOR_DP_SPARE0 ; 
 int SOR_DP_SPARE_DISP_VIDEO_PREAMBLE ; 
 int SOR_DP_SPARE_MACRO_SOR_CLK ; 
 int SOR_DP_SPARE_PANEL_INTERNAL ; 
 int SOR_DP_SPARE_SEQ_ENABLE ; 
 int SOR_ENABLE (int) ; 
 scalar_t__ SOR_HDMI_CTRL ; 
 int SOR_HDMI_CTRL_AUDIO_LAYOUT ; 
 int SOR_HDMI_CTRL_ENABLE ; 
 int SOR_HDMI_CTRL_MAX_AC_PACKET (unsigned int) ; 
 int SOR_HDMI_CTRL_REKEY (int) ; 
 int SOR_HEAD_STATE_COLORSPACE_MASK ; 
 int SOR_HEAD_STATE_COLORSPACE_RGB ; 
 int SOR_HEAD_STATE_DYNRANGE_MASK ; 
 int SOR_HEAD_STATE_RANGECOMPRESS_MASK ; 
 scalar_t__ SOR_INPUT_CONTROL ; 
 int SOR_INPUT_CONTROL_ARM_VIDEO_RANGE_LIMITED ; 
 int SOR_INPUT_CONTROL_HDMI_SRC_SELECT (scalar_t__) ; 
 scalar_t__ SOR_LANE_DRIVE_CURRENT0 ; 
 scalar_t__ SOR_LANE_PREEMPHASIS0 ; 
 scalar_t__ SOR_LANE_SEQ_CTL ; 
 int SOR_LANE_SEQ_CTL_DELAY (int) ; 
 int SOR_LANE_SEQ_CTL_POWER_STATE_UP ; 
 int SOR_LANE_SEQ_CTL_SEQUENCE_DOWN ; 
 int SOR_LANE_SEQ_CTL_STATE_BUSY ; 
 int SOR_LANE_SEQ_CTL_TRIGGER ; 
 int SOR_PLL0_FILTER (int /*<<< orphan*/ ) ; 
 int SOR_PLL0_FILTER_MASK ; 
 int SOR_PLL0_ICHPMP (int /*<<< orphan*/ ) ; 
 int SOR_PLL0_ICHPMP_MASK ; 
 int SOR_PLL0_PWR ; 
 int SOR_PLL0_VCOCAP (int /*<<< orphan*/ ) ; 
 int SOR_PLL0_VCOCAP_MASK ; 
 int SOR_PLL0_VCOPD ; 
 int SOR_PLL1_LOADADJ (int /*<<< orphan*/ ) ; 
 int SOR_PLL1_LOADADJ_MASK ; 
 int SOR_PLL1_TMDS_TERM ; 
 int SOR_PLL1_TMDS_TERMADJ (int /*<<< orphan*/ ) ; 
 int SOR_PLL1_TMDS_TERMADJ_MASK ; 
 int SOR_PLL2_BANDGAP_POWERDOWN ; 
 int SOR_PLL2_PORT_POWERDOWN ; 
 int SOR_PLL2_POWERDOWN_OVERRIDE ; 
 int SOR_PLL2_SEQ_PLLCAPPD_ENFORCE ; 
 int SOR_PLL3_AVDD10_LEVEL (int /*<<< orphan*/ ) ; 
 int SOR_PLL3_AVDD10_LEVEL_MASK ; 
 int SOR_PLL3_AVDD14_LEVEL (int /*<<< orphan*/ ) ; 
 int SOR_PLL3_AVDD14_LEVEL_MASK ; 
 int SOR_PLL3_BG_TEMP_COEF (int /*<<< orphan*/ ) ; 
 int SOR_PLL3_BG_TEMP_COEF_MASK ; 
 int SOR_PLL3_BG_VREF_LEVEL (int /*<<< orphan*/ ) ; 
 int SOR_PLL3_BG_VREF_LEVEL_MASK ; 
 int SOR_PLL3_PLL_VDD_MODE_3V3 ; 
 scalar_t__ SOR_REFCLK ; 
 int SOR_REFCLK_DIV_FRAC (unsigned int) ; 
 int SOR_REFCLK_DIV_INT (unsigned int) ; 
 int SOR_REKEY ; 
 scalar_t__ SOR_SEQ_CTL ; 
 int SOR_SEQ_CTL_PD_PC (int) ; 
 int SOR_SEQ_CTL_PD_PC_ALT (int) ; 
 int SOR_SEQ_CTL_PU_PC (int /*<<< orphan*/ ) ; 
 int SOR_SEQ_CTL_PU_PC_ALT (int /*<<< orphan*/ ) ; 
 scalar_t__ SOR_SEQ_INST (int) ; 
 int SOR_SEQ_INST_DRIVE_PWM_OUT_LO ; 
 int SOR_SEQ_INST_HALT ; 
 int SOR_SEQ_INST_WAIT (int) ; 
 int SOR_SEQ_INST_WAIT_VSYNC ; 
 scalar_t__ SOR_STATE1 ; 
 int SOR_STATE_ASY_OWNER (scalar_t__) ; 
 int SOR_STATE_ASY_OWNER_MASK ; 
 int SOR_STATE_ASY_PROTOCOL_MASK ; 
 int SOR_STATE_ASY_PROTOCOL_SINGLE_TMDS_A ; 
 scalar_t__ SOR_XBAR_CTRL ; 
 int SOR_XBAR_CTRL_LINK0_XSEL (unsigned int,int /*<<< orphan*/ ) ; 
 int SOR_XBAR_CTRL_LINK1_XSEL (unsigned int,unsigned int) ; 
 scalar_t__ SOR_XBAR_POL ; 
 int VSYNC_H_POSITION (int) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 
 int tegra_io_pad_power_enable (int /*<<< orphan*/ ) ; 
 int tegra_sor_attach (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_audio_prepare (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_disable_audio_infoframe (struct tegra_sor*) ; 
 struct tegra_sor_hdmi_settings* tegra_sor_hdmi_find_settings (struct tegra_sor*,int) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_scdc_start (struct tegra_sor*) ; 
 int tegra_sor_hdmi_setup_avi_infoframe (struct tegra_sor*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  tegra_sor_mode_set (struct tegra_sor*,struct drm_display_mode*,struct tegra_sor_state*) ; 
 int tegra_sor_power_up (struct tegra_sor*,int) ; 
 int tegra_sor_readl (struct tegra_sor*,scalar_t__) ; 
 int tegra_sor_set_parent_clock (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_update (struct tegra_sor*) ; 
 int tegra_sor_wakeup (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,scalar_t__) ; 
 struct tegra_sor* to_sor (struct tegra_output*) ; 
 struct tegra_sor_state* to_sor_state (int /*<<< orphan*/ ) ; 
 struct tegra_dc* to_tegra_dc (TYPE_6__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tegra_sor_hdmi_enable(struct drm_encoder *encoder)
{
	struct tegra_output *output = encoder_to_output(encoder);
	unsigned int h_ref_to_sync = 1, pulse_start, max_ac;
	struct tegra_dc *dc = to_tegra_dc(encoder->crtc);
	struct tegra_sor_hdmi_settings *settings;
	struct tegra_sor *sor = to_sor(output);
	struct tegra_sor_state *state;
	struct drm_display_mode *mode;
	unsigned long rate, pclk;
	unsigned int div, i;
	u32 value;
	int err;

	state = to_sor_state(output->connector.state);
	mode = &encoder->crtc->state->adjusted_mode;
	pclk = mode->clock * 1000;

	pm_runtime_get_sync(sor->dev);

	/* switch to safe parent clock */
	err = tegra_sor_set_parent_clock(sor, sor->clk_safe);
	if (err < 0) {
		dev_err(sor->dev, "failed to set safe parent clock: %d\n", err);
		return;
	}

	div = clk_get_rate(sor->clk) / 1000000 * 4;

	err = tegra_io_pad_power_enable(sor->pad);
	if (err < 0)
		dev_err(sor->dev, "failed to power on I/O pad: %d\n", err);

	usleep_range(20, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_BANDGAP_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->pll3);
	value &= ~SOR_PLL3_PLL_VDD_MODE_3V3;
	tegra_sor_writel(sor, value, sor->soc->regs->pll3);

	value = tegra_sor_readl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_VCOPD;
	value &= ~SOR_PLL0_PWR;
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_SEQ_PLLCAPPD_ENFORCE;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(200, 400);

	value = tegra_sor_readl(sor, sor->soc->regs->pll2);
	value &= ~SOR_PLL2_POWERDOWN_OVERRIDE;
	value &= ~SOR_PLL2_PORT_POWERDOWN;
	tegra_sor_writel(sor, value, sor->soc->regs->pll2);

	usleep_range(20, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PD_TXD_3 | SOR_DP_PADCTL_PD_TXD_0 |
		 SOR_DP_PADCTL_PD_TXD_1 | SOR_DP_PADCTL_PD_TXD_2;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	while (true) {
		value = tegra_sor_readl(sor, SOR_LANE_SEQ_CTL);
		if ((value & SOR_LANE_SEQ_CTL_STATE_BUSY) == 0)
			break;

		usleep_range(250, 1000);
	}

	value = SOR_LANE_SEQ_CTL_TRIGGER | SOR_LANE_SEQ_CTL_SEQUENCE_DOWN |
		SOR_LANE_SEQ_CTL_POWER_STATE_UP | SOR_LANE_SEQ_CTL_DELAY(5);
	tegra_sor_writel(sor, value, SOR_LANE_SEQ_CTL);

	while (true) {
		value = tegra_sor_readl(sor, SOR_LANE_SEQ_CTL);
		if ((value & SOR_LANE_SEQ_CTL_TRIGGER) == 0)
			break;

		usleep_range(250, 1000);
	}

	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_LINK_SPEED_MASK;
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;

	if (mode->clock < 340000) {
		DRM_DEBUG_KMS("setting 2.7 GHz link speed\n");
		value |= SOR_CLK_CNTRL_DP_LINK_SPEED_G2_70;
	} else {
		DRM_DEBUG_KMS("setting 5.4 GHz link speed\n");
		value |= SOR_CLK_CNTRL_DP_LINK_SPEED_G5_40;
	}

	value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK;
	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	/* SOR pad PLL stabilization time */
	usleep_range(250, 1000);

	value = tegra_sor_readl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_LANE_COUNT_MASK;
	value |= SOR_DP_LINKCTL_LANE_COUNT(4);
	tegra_sor_writel(sor, value, SOR_DP_LINKCTL0);

	value = tegra_sor_readl(sor, SOR_DP_SPARE0);
	value &= ~SOR_DP_SPARE_DISP_VIDEO_PREAMBLE;
	value &= ~SOR_DP_SPARE_PANEL_INTERNAL;
	value &= ~SOR_DP_SPARE_SEQ_ENABLE;
	value &= ~SOR_DP_SPARE_MACRO_SOR_CLK;
	tegra_sor_writel(sor, value, SOR_DP_SPARE0);

	value = SOR_SEQ_CTL_PU_PC(0) | SOR_SEQ_CTL_PU_PC_ALT(0) |
		SOR_SEQ_CTL_PD_PC(8) | SOR_SEQ_CTL_PD_PC_ALT(8);
	tegra_sor_writel(sor, value, SOR_SEQ_CTL);

	value = SOR_SEQ_INST_DRIVE_PWM_OUT_LO | SOR_SEQ_INST_HALT |
		SOR_SEQ_INST_WAIT_VSYNC | SOR_SEQ_INST_WAIT(1);
	tegra_sor_writel(sor, value, SOR_SEQ_INST(0));
	tegra_sor_writel(sor, value, SOR_SEQ_INST(8));

	if (!sor->soc->has_nvdisplay) {
		/* program the reference clock */
		value = SOR_REFCLK_DIV_INT(div) | SOR_REFCLK_DIV_FRAC(div);
		tegra_sor_writel(sor, value, SOR_REFCLK);
	}

	/* XXX not in TRM */
	for (value = 0, i = 0; i < 5; i++)
		value |= SOR_XBAR_CTRL_LINK0_XSEL(i, sor->xbar_cfg[i]) |
			 SOR_XBAR_CTRL_LINK1_XSEL(i, i);

	tegra_sor_writel(sor, 0x00000000, SOR_XBAR_POL);
	tegra_sor_writel(sor, value, SOR_XBAR_CTRL);

	/* switch to parent clock */
	err = clk_set_parent(sor->clk, sor->clk_parent);
	if (err < 0) {
		dev_err(sor->dev, "failed to set parent clock: %d\n", err);
		return;
	}

	err = tegra_sor_set_parent_clock(sor, sor->clk_pad);
	if (err < 0) {
		dev_err(sor->dev, "failed to set pad clock: %d\n", err);
		return;
	}

	/* adjust clock rate for HDMI 2.0 modes */
	rate = clk_get_rate(sor->clk_parent);

	if (mode->clock >= 340000)
		rate /= 2;

	DRM_DEBUG_KMS("setting clock to %lu Hz, mode: %lu Hz\n", rate, pclk);

	clk_set_rate(sor->clk, rate);

	if (!sor->soc->has_nvdisplay) {
		value = SOR_INPUT_CONTROL_HDMI_SRC_SELECT(dc->pipe);

		/* XXX is this the proper check? */
		if (mode->clock < 75000)
			value |= SOR_INPUT_CONTROL_ARM_VIDEO_RANGE_LIMITED;

		tegra_sor_writel(sor, value, SOR_INPUT_CONTROL);
	}

	max_ac = ((mode->htotal - mode->hdisplay) - SOR_REKEY - 18) / 32;

	value = SOR_HDMI_CTRL_ENABLE | SOR_HDMI_CTRL_MAX_AC_PACKET(max_ac) |
		SOR_HDMI_CTRL_AUDIO_LAYOUT | SOR_HDMI_CTRL_REKEY(SOR_REKEY);
	tegra_sor_writel(sor, value, SOR_HDMI_CTRL);

	if (!dc->soc->has_nvdisplay) {
		/* H_PULSE2 setup */
		pulse_start = h_ref_to_sync +
			      (mode->hsync_end - mode->hsync_start) +
			      (mode->htotal - mode->hsync_end) - 10;

		value = PULSE_LAST_END_A | PULSE_QUAL_VACTIVE |
			PULSE_POLARITY_HIGH | PULSE_MODE_NORMAL;
		tegra_dc_writel(dc, value, DC_DISP_H_PULSE2_CONTROL);

		value = PULSE_END(pulse_start + 8) | PULSE_START(pulse_start);
		tegra_dc_writel(dc, value, DC_DISP_H_PULSE2_POSITION_A);

		value = tegra_dc_readl(dc, DC_DISP_DISP_SIGNAL_OPTIONS0);
		value |= H_PULSE2_ENABLE;
		tegra_dc_writel(dc, value, DC_DISP_DISP_SIGNAL_OPTIONS0);
	}

	/* infoframe setup */
	err = tegra_sor_hdmi_setup_avi_infoframe(sor, mode);
	if (err < 0)
		dev_err(sor->dev, "failed to setup AVI infoframe: %d\n", err);

	/* XXX HDMI audio support not implemented yet */
	tegra_sor_hdmi_disable_audio_infoframe(sor);

	/* use single TMDS protocol */
	value = tegra_sor_readl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_PROTOCOL_MASK;
	value |= SOR_STATE_ASY_PROTOCOL_SINGLE_TMDS_A;
	tegra_sor_writel(sor, value, SOR_STATE1);

	/* power up pad calibration */
	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	/* production settings */
	settings = tegra_sor_hdmi_find_settings(sor, mode->clock * 1000);
	if (!settings) {
		dev_err(sor->dev, "no settings for pixel clock %d Hz\n",
			mode->clock * 1000);
		return;
	}

	value = tegra_sor_readl(sor, sor->soc->regs->pll0);
	value &= ~SOR_PLL0_ICHPMP_MASK;
	value &= ~SOR_PLL0_FILTER_MASK;
	value &= ~SOR_PLL0_VCOCAP_MASK;
	value |= SOR_PLL0_ICHPMP(settings->ichpmp);
	value |= SOR_PLL0_FILTER(settings->filter);
	value |= SOR_PLL0_VCOCAP(settings->vcocap);
	tegra_sor_writel(sor, value, sor->soc->regs->pll0);

	/* XXX not in TRM */
	value = tegra_sor_readl(sor, sor->soc->regs->pll1);
	value &= ~SOR_PLL1_LOADADJ_MASK;
	value &= ~SOR_PLL1_TMDS_TERMADJ_MASK;
	value |= SOR_PLL1_LOADADJ(settings->loadadj);
	value |= SOR_PLL1_TMDS_TERMADJ(settings->tmds_termadj);
	value |= SOR_PLL1_TMDS_TERM;
	tegra_sor_writel(sor, value, sor->soc->regs->pll1);

	value = tegra_sor_readl(sor, sor->soc->regs->pll3);
	value &= ~SOR_PLL3_BG_TEMP_COEF_MASK;
	value &= ~SOR_PLL3_BG_VREF_LEVEL_MASK;
	value &= ~SOR_PLL3_AVDD10_LEVEL_MASK;
	value &= ~SOR_PLL3_AVDD14_LEVEL_MASK;
	value |= SOR_PLL3_BG_TEMP_COEF(settings->bg_temp_coef);
	value |= SOR_PLL3_BG_VREF_LEVEL(settings->bg_vref_level);
	value |= SOR_PLL3_AVDD10_LEVEL(settings->avdd10_level);
	value |= SOR_PLL3_AVDD14_LEVEL(settings->avdd14_level);
	tegra_sor_writel(sor, value, sor->soc->regs->pll3);

	value = settings->drive_current[3] << 24 |
		settings->drive_current[2] << 16 |
		settings->drive_current[1] <<  8 |
		settings->drive_current[0] <<  0;
	tegra_sor_writel(sor, value, SOR_LANE_DRIVE_CURRENT0);

	value = settings->preemphasis[3] << 24 |
		settings->preemphasis[2] << 16 |
		settings->preemphasis[1] <<  8 |
		settings->preemphasis[0] <<  0;
	tegra_sor_writel(sor, value, SOR_LANE_PREEMPHASIS0);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value &= ~SOR_DP_PADCTL_TX_PU_MASK;
	value |= SOR_DP_PADCTL_TX_PU_ENABLE;
	value |= SOR_DP_PADCTL_TX_PU(settings->tx_pu_value);
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl2);
	value &= ~SOR_DP_PADCTL_SPAREPLL_MASK;
	value |= SOR_DP_PADCTL_SPAREPLL(settings->sparepll);
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl2);

	/* power down pad calibration */
	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_PAD_CAL_PD;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	if (!dc->soc->has_nvdisplay) {
		/* miscellaneous display controller settings */
		value = VSYNC_H_POSITION(1);
		tegra_dc_writel(dc, value, DC_DISP_DISP_TIMING_OPTIONS);
	}

	value = tegra_dc_readl(dc, DC_DISP_DISP_COLOR_CONTROL);
	value &= ~DITHER_CONTROL_MASK;
	value &= ~BASE_COLOR_SIZE_MASK;

	switch (state->bpc) {
	case 6:
		value |= BASE_COLOR_SIZE_666;
		break;

	case 8:
		value |= BASE_COLOR_SIZE_888;
		break;

	case 10:
		value |= BASE_COLOR_SIZE_101010;
		break;

	case 12:
		value |= BASE_COLOR_SIZE_121212;
		break;

	default:
		WARN(1, "%u bits-per-color not supported\n", state->bpc);
		value |= BASE_COLOR_SIZE_888;
		break;
	}

	tegra_dc_writel(dc, value, DC_DISP_DISP_COLOR_CONTROL);

	/* XXX set display head owner */
	value = tegra_sor_readl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_OWNER_MASK;
	value |= SOR_STATE_ASY_OWNER(1 + dc->pipe);
	tegra_sor_writel(sor, value, SOR_STATE1);

	err = tegra_sor_power_up(sor, 250);
	if (err < 0)
		dev_err(sor->dev, "failed to power up SOR: %d\n", err);

	/* configure dynamic range of output */
	value = tegra_sor_readl(sor, sor->soc->regs->head_state0 + dc->pipe);
	value &= ~SOR_HEAD_STATE_RANGECOMPRESS_MASK;
	value &= ~SOR_HEAD_STATE_DYNRANGE_MASK;
	tegra_sor_writel(sor, value, sor->soc->regs->head_state0 + dc->pipe);

	/* configure colorspace */
	value = tegra_sor_readl(sor, sor->soc->regs->head_state0 + dc->pipe);
	value &= ~SOR_HEAD_STATE_COLORSPACE_MASK;
	value |= SOR_HEAD_STATE_COLORSPACE_RGB;
	tegra_sor_writel(sor, value, sor->soc->regs->head_state0 + dc->pipe);

	tegra_sor_mode_set(sor, mode, state);

	tegra_sor_update(sor);

	/* program preamble timing in SOR (XXX) */
	value = tegra_sor_readl(sor, SOR_DP_SPARE0);
	value &= ~SOR_DP_SPARE_DISP_VIDEO_PREAMBLE;
	tegra_sor_writel(sor, value, SOR_DP_SPARE0);

	err = tegra_sor_attach(sor);
	if (err < 0)
		dev_err(sor->dev, "failed to attach SOR: %d\n", err);

	/* enable display to SOR clock and generate HDMI preamble */
	value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);

	if (!sor->soc->has_nvdisplay)
		value |= SOR_ENABLE(1) | SOR1_TIMING_CYA;
	else
		value |= SOR_ENABLE(sor->index);

	tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	if (dc->soc->has_nvdisplay) {
		value = tegra_dc_readl(dc, DC_DISP_CORE_SOR_SET_CONTROL(sor->index));
		value &= ~PROTOCOL_MASK;
		value |= PROTOCOL_SINGLE_TMDS_A;
		tegra_dc_writel(dc, value, DC_DISP_CORE_SOR_SET_CONTROL(sor->index));
	}

	tegra_dc_commit(dc);

	err = tegra_sor_wakeup(sor);
	if (err < 0)
		dev_err(sor->dev, "failed to wakeup SOR: %d\n", err);

	tegra_sor_hdmi_scdc_start(sor);
	tegra_sor_audio_prepare(sor);
}