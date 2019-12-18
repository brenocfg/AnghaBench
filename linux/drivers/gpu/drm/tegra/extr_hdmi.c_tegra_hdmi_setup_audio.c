#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_hdmi_audio_config {int /*<<< orphan*/  aval; int /*<<< orphan*/  cts; scalar_t__ n; } ;
struct TYPE_3__ {int channels; int /*<<< orphan*/  sample_rate; } ;
struct tegra_hdmi {int audio_source; TYPE_2__* config; int /*<<< orphan*/  pixel_clock; int /*<<< orphan*/  dev; TYPE_1__ format; } ;
struct TYPE_4__ {scalar_t__ has_hda; scalar_t__ has_hbr; } ;

/* Variables and functions */
 int ACR_ENABLE ; 
 int ACR_SUBPACK_CTS (int /*<<< orphan*/ ) ; 
 int ACR_SUBPACK_N (scalar_t__) ; 
 int AUDIO_CNTRL0_ERROR_TOLERANCE (int) ; 
 int AUDIO_CNTRL0_FRAMES_PER_BLOCK (int) ; 
 int AUDIO_CNTRL0_SOURCE_SELECT_AUTO ; 
 int AUDIO_CNTRL0_SOURCE_SELECT_SPDIF ; 
 int AUDIO_N_GENERATE_ALTERNATE ; 
 int AUDIO_N_RESETF ; 
 int AUDIO_N_VALUE (scalar_t__) ; 
 int EINVAL ; 
#define  HDA 129 
 int /*<<< orphan*/  HDMI_NV_PDISP_AUDIO_CNTRL0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_AUDIO_N ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_ACR_CTRL ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_SPARE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_CNTRL0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_SPARE0 ; 
 int SOR_AUDIO_CNTRL0_INJECT_NULLSMPL ; 
 int SOR_AUDIO_CNTRL0_SOURCE_SELECT_AUTO ; 
 int SOR_AUDIO_CNTRL0_SOURCE_SELECT_HDAL ; 
 int SOR_AUDIO_CNTRL0_SOURCE_SELECT_SPDIF ; 
 int SOR_AUDIO_SPARE0_HBR_ENABLE ; 
 int SPARE_CTS_RESET_VAL (int) ; 
 int SPARE_FORCE_SW_CTS ; 
 int SPARE_HW_CTS ; 
#define  SPDIF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_hdmi_get_audio_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_hdmi_audio_config*) ; 
 int tegra_hdmi_readl (struct tegra_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_setup_audio_fs_tables (struct tegra_hdmi*) ; 
 int /*<<< orphan*/  tegra_hdmi_write_aval (struct tegra_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_writel (struct tegra_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hdmi_setup_audio(struct tegra_hdmi *hdmi)
{
	struct tegra_hdmi_audio_config config;
	u32 source, value;
	int err;

	switch (hdmi->audio_source) {
	case HDA:
		if (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_HDAL;
		else
			return -EINVAL;

		break;

	case SPDIF:
		if (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_SPDIF;
		else
			source = AUDIO_CNTRL0_SOURCE_SELECT_SPDIF;
		break;

	default:
		if (hdmi->config->has_hda)
			source = SOR_AUDIO_CNTRL0_SOURCE_SELECT_AUTO;
		else
			source = AUDIO_CNTRL0_SOURCE_SELECT_AUTO;
		break;
	}

	/*
	 * Tegra30 and later use a slightly modified version of the register
	 * layout to accomodate for changes related to supporting HDA as the
	 * audio input source for HDMI. The source select field has moved to
	 * the SOR_AUDIO_CNTRL0 register, but the error tolerance and frames
	 * per block fields remain in the AUDIO_CNTRL0 register.
	 */
	if (hdmi->config->has_hda) {
		/*
		 * Inject null samples into the audio FIFO for every frame in
		 * which the codec did not receive any samples. This applies
		 * to stereo LPCM only.
		 *
		 * XXX: This seems to be a remnant of MCP days when this was
		 * used to work around issues with monitors not being able to
		 * play back system startup sounds early. It is possibly not
		 * needed on Linux at all.
		 */
		if (hdmi->format.channels == 2)
			value = SOR_AUDIO_CNTRL0_INJECT_NULLSMPL;
		else
			value = 0;

		value |= source;

		tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_CNTRL0);
	}

	/*
	 * On Tegra20, HDA is not a supported audio source and the source
	 * select field is part of the AUDIO_CNTRL0 register.
	 */
	value = AUDIO_CNTRL0_FRAMES_PER_BLOCK(0xc0) |
		AUDIO_CNTRL0_ERROR_TOLERANCE(6);

	if (!hdmi->config->has_hda)
		value |= source;

	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_AUDIO_CNTRL0);

	/*
	 * Advertise support for High Bit-Rate on Tegra114 and later.
	 */
	if (hdmi->config->has_hbr) {
		value = tegra_hdmi_readl(hdmi, HDMI_NV_PDISP_SOR_AUDIO_SPARE0);
		value |= SOR_AUDIO_SPARE0_HBR_ENABLE;
		tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_SPARE0);
	}

	err = tegra_hdmi_get_audio_config(hdmi->format.sample_rate,
					  hdmi->pixel_clock, &config);
	if (err < 0) {
		dev_err(hdmi->dev,
			"cannot set audio to %u Hz at %u Hz pixel clock\n",
			hdmi->format.sample_rate, hdmi->pixel_clock);
		return err;
	}

	dev_dbg(hdmi->dev, "audio: pixclk=%u, n=%u, cts=%u, aval=%u\n",
		hdmi->pixel_clock, config.n, config.cts, config.aval);

	tegra_hdmi_writel(hdmi, 0, HDMI_NV_PDISP_HDMI_ACR_CTRL);

	value = AUDIO_N_RESETF | AUDIO_N_GENERATE_ALTERNATE |
		AUDIO_N_VALUE(config.n - 1);
	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_AUDIO_N);

	tegra_hdmi_writel(hdmi, ACR_SUBPACK_N(config.n) | ACR_ENABLE,
			  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_HIGH);

	tegra_hdmi_writel(hdmi, ACR_SUBPACK_CTS(config.cts),
			  HDMI_NV_PDISP_HDMI_ACR_0441_SUBPACK_LOW);

	value = SPARE_HW_CTS | SPARE_FORCE_SW_CTS | SPARE_CTS_RESET_VAL(1);
	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_HDMI_SPARE);

	value = tegra_hdmi_readl(hdmi, HDMI_NV_PDISP_AUDIO_N);
	value &= ~AUDIO_N_RESETF;
	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_AUDIO_N);

	if (hdmi->config->has_hda)
		tegra_hdmi_write_aval(hdmi, config.aval);

	tegra_hdmi_setup_audio_fs_tables(hdmi);

	return 0;
}