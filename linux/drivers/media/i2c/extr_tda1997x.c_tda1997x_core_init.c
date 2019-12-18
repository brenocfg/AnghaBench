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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_platform_data {int* vidout_port_cfg; int audout_mclk_fs; } ;
struct tda1997x_state {scalar_t__ chip_revision; void* hdmi_status; int /*<<< orphan*/  client; struct tda1997x_platform_data pdata; } ;

/* Variables and functions */
 int AUDIO_CLOCK_SEL_128FS ; 
 int AUDIO_CLOCK_SEL_16FS ; 
 int AUDIO_CLOCK_SEL_256FS ; 
 int AUDIO_CLOCK_SEL_32FS ; 
 int AUDIO_CLOCK_SEL_512FS ; 
 int AUDIO_CLOCK_SEL_64FS ; 
 int CGU_DBG_CLK_SEL_SHIFT ; 
 int /*<<< orphan*/  CLK_MAX_RATE ; 
 int /*<<< orphan*/  CLK_MIN_RATE ; 
 int DC_FILTER_VAL ; 
 int HDCP_FAST_REAUTH ; 
 int HDCP_HDMI ; 
 int HDMI_CTRL_HDCP_AUTO ; 
 int HDMI_CTRL_HDCP_SHIFT ; 
 int HDMI_CTRL_MUTE_AUTO ; 
 int HDMI_CTRL_MUTE_SHIFT ; 
 int HPD_AUTO_HPD_UNSEL ; 
 int /*<<< orphan*/  HPD_LOW_BP ; 
 int INTERRUPT_AUDIO ; 
 int INTERRUPT_HDCP ; 
 int INTERRUPT_INFO ; 
 int INTERRUPT_RATE ; 
 int INTERRUPT_SUS ; 
 int MAN_DIS_HDCP ; 
 int MAN_RST_HDCP ; 
 int MASK_AUDIO_FLG ; 
 int MASK_AUDIO_FREQ_FLG ; 
 int MASK_AUD_IF ; 
 int MASK_AVI_IF ; 
 int MASK_DET_5V ; 
 int MASK_ERROR_FIFO_PT ; 
 int MASK_FMT ; 
 int MASK_MPT ; 
 int MASK_MUTE_FLG ; 
 int MASK_RATE_A_ST ; 
 int MASK_RATE_B_ST ; 
 int MASK_SPD_IF ; 
 int MASK_STATE_C5 ; 
 int MASK_SUS_END ; 
 int /*<<< orphan*/  NACK_HDCP ; 
 scalar_t__ REG_AUDIO_CLOCK ; 
 scalar_t__ REG_CGU_DBG_SEL ; 
 int /*<<< orphan*/  REG_CLK_MAX_RATE ; 
 int /*<<< orphan*/  REG_CLK_MIN_RATE ; 
 scalar_t__ REG_CMTP_REG10 ; 
 int REG_CONTROL ; 
 scalar_t__ REG_DEEP_COLOR_CTRL ; 
 int REG_EN_OSC_PERIOD_LSB ; 
 scalar_t__ REG_HDCP_BCAPS ; 
 scalar_t__ REG_HDMI_CTRL ; 
 scalar_t__ REG_HDMI_FLAGS ; 
 scalar_t__ REG_HPD_AUTO_CTRL ; 
 scalar_t__ REG_INFO_CTRL ; 
 scalar_t__ REG_INFO_EXCEED ; 
 scalar_t__ REG_INT_FLG_CLR_AFE ; 
 scalar_t__ REG_INT_FLG_CLR_AUDIO ; 
 scalar_t__ REG_INT_FLG_CLR_DDC ; 
 scalar_t__ REG_INT_FLG_CLR_HDCP ; 
 scalar_t__ REG_INT_FLG_CLR_INFO ; 
 scalar_t__ REG_INT_FLG_CLR_MODE ; 
 scalar_t__ REG_INT_FLG_CLR_RATE ; 
 scalar_t__ REG_INT_FLG_CLR_SUS ; 
 scalar_t__ REG_INT_FLG_CLR_TOP ; 
 scalar_t__ REG_INT_MASK_AFE ; 
 scalar_t__ REG_INT_MASK_AUDIO ; 
 scalar_t__ REG_INT_MASK_DDC ; 
 scalar_t__ REG_INT_MASK_HDCP ; 
 scalar_t__ REG_INT_MASK_INFO ; 
 scalar_t__ REG_INT_MASK_MODE ; 
 scalar_t__ REG_INT_MASK_RATE ; 
 scalar_t__ REG_INT_MASK_SUS ; 
 scalar_t__ REG_INT_MASK_TOP ; 
 scalar_t__ REG_MAN_SUS_HDMI_SEL ; 
 int REG_OSC_DIVIDER ; 
 int REG_PWR_CONTROL ; 
 scalar_t__ REG_RT_MAN_CTRL ; 
 scalar_t__ REG_SUS_SET_RGB2 ; 
 scalar_t__ REG_SUS_SET_RGB3 ; 
 scalar_t__ REG_SVC_MODE ; 
 scalar_t__ REG_TIMER_D ; 
 scalar_t__ REG_VDP_CTRL ; 
 scalar_t__ REG_VERSION ; 
 scalar_t__ REG_VP35_32_CTRL ; 
 scalar_t__ REG_WDL_CFG ; 
 int /*<<< orphan*/  RESET_AI ; 
 int /*<<< orphan*/  RESET_AUDIO ; 
 int /*<<< orphan*/  RESET_GAMUT ; 
 int /*<<< orphan*/  RESET_IF ; 
 int RT_MAN_CTRL_RT ; 
 int RT_MAN_CTRL_RT_A ; 
 int RT_MAN_CTRL_RT_B ; 
 int VDP_CTRL_MATRIX_BP ; 
 int WDL_CFG_VAL ; 
 int /*<<< orphan*/  debug ; 
 void* io_read (struct v4l2_subdev*,scalar_t__) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,scalar_t__,int) ; 
 int /*<<< orphan*/  io_write24 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int tda1997x_cec_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  tda1997x_cec_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  tda1997x_configure_audout (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda1997x_configure_vidout (struct tda1997x_state*) ; 
 int /*<<< orphan*/  tda1997x_hdmi_info_reset (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda1997x_manual_hpd (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda1997x_reset_n1 (struct tda1997x_state*) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int tda1997x_core_init(struct v4l2_subdev *sd)
{
	struct tda1997x_state *state = to_state(sd);
	struct tda1997x_platform_data *pdata = &state->pdata;
	u8 reg;
	int i;

	/* disable HPD */
	io_write(sd, REG_HPD_AUTO_CTRL, HPD_AUTO_HPD_UNSEL);
	if (state->chip_revision == 0) {
		io_write(sd, REG_MAN_SUS_HDMI_SEL, MAN_DIS_HDCP | MAN_RST_HDCP);
		io_write(sd, REG_CGU_DBG_SEL, 1 << CGU_DBG_CLK_SEL_SHIFT);
	}

	/* reset infoframe at end of start-up-sequencer */
	io_write(sd, REG_SUS_SET_RGB2, 0x06);
	io_write(sd, REG_SUS_SET_RGB3, 0x06);

	/* Enable TMDS pull-ups */
	io_write(sd, REG_RT_MAN_CTRL, RT_MAN_CTRL_RT |
		 RT_MAN_CTRL_RT_B | RT_MAN_CTRL_RT_A);

	/* enable sync measurement timing */
	tda1997x_cec_write(sd, REG_PWR_CONTROL & 0xff, 0x04);
	/* adjust CEC clock divider */
	tda1997x_cec_write(sd, REG_OSC_DIVIDER & 0xff, 0x03);
	tda1997x_cec_write(sd, REG_EN_OSC_PERIOD_LSB & 0xff, 0xa0);
	io_write(sd, REG_TIMER_D, 0x54);
	/* enable power switch */
	reg = tda1997x_cec_read(sd, REG_CONTROL & 0xff);
	reg |= 0x20;
	tda1997x_cec_write(sd, REG_CONTROL & 0xff, reg);
	mdelay(50);

	/* read the chip version */
	reg = io_read(sd, REG_VERSION);
	/* get the chip configuration */
	reg = io_read(sd, REG_CMTP_REG10);

	/* enable interrupts we care about */
	io_write(sd, REG_INT_MASK_TOP,
		 INTERRUPT_HDCP | INTERRUPT_AUDIO | INTERRUPT_INFO |
		 INTERRUPT_RATE | INTERRUPT_SUS);
	/* config_mtp,fmt,sus_end,sus_st */
	io_write(sd, REG_INT_MASK_SUS, MASK_MPT | MASK_FMT | MASK_SUS_END);
	/* rate stability change for inputs A/B */
	io_write(sd, REG_INT_MASK_RATE, MASK_RATE_B_ST | MASK_RATE_A_ST);
	/* aud,spd,avi*/
	io_write(sd, REG_INT_MASK_INFO,
		 MASK_AUD_IF | MASK_SPD_IF | MASK_AVI_IF);
	/* audio_freq,audio_flg,mute_flg,fifo_err */
	io_write(sd, REG_INT_MASK_AUDIO,
		 MASK_AUDIO_FREQ_FLG | MASK_AUDIO_FLG | MASK_MUTE_FLG |
		 MASK_ERROR_FIFO_PT);
	/* HDCP C5 state reached */
	io_write(sd, REG_INT_MASK_HDCP, MASK_STATE_C5);
	/* 5V detect and HDP pulse end */
	io_write(sd, REG_INT_MASK_DDC, MASK_DET_5V);
	/* don't care about AFE/MODE */
	io_write(sd, REG_INT_MASK_AFE, 0);
	io_write(sd, REG_INT_MASK_MODE, 0);

	/* clear all interrupts */
	io_write(sd, REG_INT_FLG_CLR_TOP, 0xff);
	io_write(sd, REG_INT_FLG_CLR_SUS, 0xff);
	io_write(sd, REG_INT_FLG_CLR_DDC, 0xff);
	io_write(sd, REG_INT_FLG_CLR_RATE, 0xff);
	io_write(sd, REG_INT_FLG_CLR_MODE, 0xff);
	io_write(sd, REG_INT_FLG_CLR_INFO, 0xff);
	io_write(sd, REG_INT_FLG_CLR_AUDIO, 0xff);
	io_write(sd, REG_INT_FLG_CLR_HDCP, 0xff);
	io_write(sd, REG_INT_FLG_CLR_AFE, 0xff);

	/* init TMDS equalizer */
	if (state->chip_revision == 0)
		io_write(sd, REG_CGU_DBG_SEL, 1 << CGU_DBG_CLK_SEL_SHIFT);
	io_write24(sd, REG_CLK_MIN_RATE, CLK_MIN_RATE);
	io_write24(sd, REG_CLK_MAX_RATE, CLK_MAX_RATE);
	if (state->chip_revision == 0)
		io_write(sd, REG_WDL_CFG, WDL_CFG_VAL);
	/* DC filter */
	io_write(sd, REG_DEEP_COLOR_CTRL, DC_FILTER_VAL);
	/* disable test pattern */
	io_write(sd, REG_SVC_MODE, 0x00);
	/* update HDMI INFO CTRL */
	io_write(sd, REG_INFO_CTRL, 0xff);
	/* write HDMI INFO EXCEED value */
	io_write(sd, REG_INFO_EXCEED, 3);

	if (state->chip_revision == 0)
		tda1997x_reset_n1(state);

	/*
	 * No HDCP acknowledge when HDCP is disabled
	 * and reset SUS to force format detection
	 */
	tda1997x_hdmi_info_reset(sd, NACK_HDCP, true);

	/* Set HPD low */
	tda1997x_manual_hpd(sd, HPD_LOW_BP);

	/* Configure receiver capabilities */
	io_write(sd, REG_HDCP_BCAPS, HDCP_HDMI | HDCP_FAST_REAUTH);

	/* Configure HDMI: Auto HDCP mode, packet controlled mute */
	reg = HDMI_CTRL_MUTE_AUTO << HDMI_CTRL_MUTE_SHIFT;
	reg |= HDMI_CTRL_HDCP_AUTO << HDMI_CTRL_HDCP_SHIFT;
	io_write(sd, REG_HDMI_CTRL, reg);

	/* reset start-up-sequencer to force format detection */
	tda1997x_hdmi_info_reset(sd, 0, true);

	/* disable matrix conversion */
	reg = io_read(sd, REG_VDP_CTRL);
	reg |= VDP_CTRL_MATRIX_BP;
	io_write(sd, REG_VDP_CTRL, reg);

	/* set video output mode */
	tda1997x_configure_vidout(state);

	/* configure video output port */
	for (i = 0; i < 9; i++) {
		v4l_dbg(1, debug, state->client, "vidout_cfg[%d]=0x%02x\n", i,
			pdata->vidout_port_cfg[i]);
		io_write(sd, REG_VP35_32_CTRL + i, pdata->vidout_port_cfg[i]);
	}

	/* configure audio output port */
	tda1997x_configure_audout(sd, 0);

	/* configure audio clock freq */
	switch (pdata->audout_mclk_fs) {
	case 512:
		reg = AUDIO_CLOCK_SEL_512FS;
		break;
	case 256:
		reg = AUDIO_CLOCK_SEL_256FS;
		break;
	case 128:
		reg = AUDIO_CLOCK_SEL_128FS;
		break;
	case 64:
		reg = AUDIO_CLOCK_SEL_64FS;
		break;
	case 32:
		reg = AUDIO_CLOCK_SEL_32FS;
		break;
	default:
		reg = AUDIO_CLOCK_SEL_16FS;
		break;
	}
	io_write(sd, REG_AUDIO_CLOCK, reg);

	/* reset advanced infoframes (ISRC1/ISRC2/ACP) */
	tda1997x_hdmi_info_reset(sd, RESET_AI, false);
	/* reset infoframe */
	tda1997x_hdmi_info_reset(sd, RESET_IF, false);
	/* reset audio infoframes */
	tda1997x_hdmi_info_reset(sd, RESET_AUDIO, false);
	/* reset gamut */
	tda1997x_hdmi_info_reset(sd, RESET_GAMUT, false);

	/* get initial HDMI status */
	state->hdmi_status = io_read(sd, REG_HDMI_FLAGS);

	return 0;
}