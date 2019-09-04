#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct tda998x_priv {int tmds_clock; TYPE_1__* hdmi; } ;
struct tda998x_audio_params {int config; int format; int sample_rate; int* status; int /*<<< orphan*/  cea; int /*<<< orphan*/  sample_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AFMT_I2S 129 
#define  AFMT_SPDIF 128 
 int AIP_CLKSEL_AIP_I2S ; 
 int AIP_CLKSEL_AIP_SPDIF ; 
 int AIP_CLKSEL_FS_ACLK ; 
 int AIP_CLKSEL_FS_FS64SPDIF ; 
 int AIP_CNTRL_0_ACR_MAN ; 
 int AIP_CNTRL_0_LAYOUT ; 
 int AIP_CNTRL_0_RST_CTS ; 
 int AUDIO_DIV_SERCLK_8 ; 
 int CTS_N_K (int) ; 
 int CTS_N_M (int) ; 
 int EINVAL ; 
 int MUX_AP_SELECT_I2S ; 
 int MUX_AP_SELECT_SPDIF ; 
 int /*<<< orphan*/  REG_ACR_CTS_0 ; 
 int /*<<< orphan*/  REG_AIP_CLKSEL ; 
 int /*<<< orphan*/  REG_AIP_CNTRL_0 ; 
 int /*<<< orphan*/  REG_AUDIO_DIV ; 
 int /*<<< orphan*/  REG_CH_STAT_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CTS_N ; 
 int /*<<< orphan*/  REG_ENA_ACLK ; 
 int /*<<< orphan*/  REG_ENA_AP ; 
 int /*<<< orphan*/  REG_MUX_AP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_set (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write_range (struct tda998x_priv*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  tda998x_audio_mute (struct tda998x_priv*,int) ; 
 int tda998x_write_aif (struct tda998x_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tda998x_configure_audio(struct tda998x_priv *priv,
			struct tda998x_audio_params *params)
{
	u8 buf[6], clksel_aip, clksel_fs, cts_n, adiv;
	u32 n;

	/* Enable audio ports */
	reg_write(priv, REG_ENA_AP, params->config);

	/* Set audio input source */
	switch (params->format) {
	case AFMT_SPDIF:
		reg_write(priv, REG_ENA_ACLK, 0);
		reg_write(priv, REG_MUX_AP, MUX_AP_SELECT_SPDIF);
		clksel_aip = AIP_CLKSEL_AIP_SPDIF;
		clksel_fs = AIP_CLKSEL_FS_FS64SPDIF;
		cts_n = CTS_N_M(3) | CTS_N_K(3);
		break;

	case AFMT_I2S:
		reg_write(priv, REG_ENA_ACLK, 1);
		reg_write(priv, REG_MUX_AP, MUX_AP_SELECT_I2S);
		clksel_aip = AIP_CLKSEL_AIP_I2S;
		clksel_fs = AIP_CLKSEL_FS_ACLK;
		switch (params->sample_width) {
		case 16:
			cts_n = CTS_N_M(3) | CTS_N_K(1);
			break;
		case 18:
		case 20:
		case 24:
			cts_n = CTS_N_M(3) | CTS_N_K(2);
			break;
		default:
		case 32:
			cts_n = CTS_N_M(3) | CTS_N_K(3);
			break;
		}
		break;

	default:
		dev_err(&priv->hdmi->dev, "Unsupported I2S format\n");
		return -EINVAL;
	}

	reg_write(priv, REG_AIP_CLKSEL, clksel_aip);
	reg_clear(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_LAYOUT |
					AIP_CNTRL_0_ACR_MAN);	/* auto CTS */
	reg_write(priv, REG_CTS_N, cts_n);

	/*
	 * Audio input somehow depends on HDMI line rate which is
	 * related to pixclk. Testing showed that modes with pixclk
	 * >100MHz need a larger divider while <40MHz need the default.
	 * There is no detailed info in the datasheet, so we just
	 * assume 100MHz requires larger divider.
	 */
	adiv = AUDIO_DIV_SERCLK_8;
	if (priv->tmds_clock > 100000)
		adiv++;			/* AUDIO_DIV_SERCLK_16 */

	/* S/PDIF asks for a larger divider */
	if (params->format == AFMT_SPDIF)
		adiv++;			/* AUDIO_DIV_SERCLK_16 or _32 */

	reg_write(priv, REG_AUDIO_DIV, adiv);

	/*
	 * This is the approximate value of N, which happens to be
	 * the recommended values for non-coherent clocks.
	 */
	n = 128 * params->sample_rate / 1000;

	/* Write the CTS and N values */
	buf[0] = 0x44;
	buf[1] = 0x42;
	buf[2] = 0x01;
	buf[3] = n;
	buf[4] = n >> 8;
	buf[5] = n >> 16;
	reg_write_range(priv, REG_ACR_CTS_0, buf, 6);

	/* Set CTS clock reference */
	reg_write(priv, REG_AIP_CLKSEL, clksel_aip | clksel_fs);

	/* Reset CTS generator */
	reg_set(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_CTS);
	reg_clear(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_CTS);

	/* Write the channel status
	 * The REG_CH_STAT_B-registers skip IEC958 AES2 byte, because
	 * there is a separate register for each I2S wire.
	 */
	buf[0] = params->status[0];
	buf[1] = params->status[1];
	buf[2] = params->status[3];
	buf[3] = params->status[4];
	reg_write_range(priv, REG_CH_STAT_B(0), buf, 4);

	tda998x_audio_mute(priv, true);
	msleep(20);
	tda998x_audio_mute(priv, false);

	return tda998x_write_aif(priv, &params->cea);
}