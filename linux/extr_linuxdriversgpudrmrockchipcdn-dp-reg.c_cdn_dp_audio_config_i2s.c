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
typedef  int u32 ;
struct TYPE_2__ {int num_lanes; } ;
struct cdn_dp_device {scalar_t__ regs; TYPE_1__ link; } ;
struct audio_info {int channels; int sample_width; int sample_rate; } ;

/* Variables and functions */
 int AUDIO_CH_NUM (int) ; 
 scalar_t__ AUDIO_SRC_CNFG ; 
 scalar_t__ AUDIO_SRC_CNTL ; 
 int AUDIO_TYPE_LPCM ; 
 int CFG_SUB_PCKT_NUM (int) ; 
 scalar_t__ COM_CH_STTS_BITS ; 
 scalar_t__ FIFO_CNTL ; 
 int I2S_DEC_PORT_EN (int) ; 
 int I2S_DEC_START ; 
 int MAX_NUM_CH (int) ; 
 int NUM_OF_I2S_PORTS (int) ; 
 int ORIGINAL_SAMP_FREQ (int) ; 
 int SAMPLING_FREQ (int) ; 
 scalar_t__ SMPL2PKT_CNFG ; 
 scalar_t__ SMPL2PKT_CNTL ; 
 int SMPL2PKT_EN ; 
 scalar_t__ SPDIF_CTRL_ADDR ; 
 scalar_t__ STTS_BIT_CH (int) ; 
 int SYNC_WR_TO_CH_ZERO ; 
 int TRANS_SMPL_WIDTH_32 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdn_dp_audio_config_i2s(struct cdn_dp_device *dp,
				    struct audio_info *audio)
{
	int sub_pckt_num = 1, i2s_port_en_val = 0xf, i;
	u32 val;

	if (audio->channels == 2) {
		if (dp->link.num_lanes == 1)
			sub_pckt_num = 2;
		else
			sub_pckt_num = 4;

		i2s_port_en_val = 1;
	} else if (audio->channels == 4) {
		i2s_port_en_val = 3;
	}

	writel(0x0, dp->regs + SPDIF_CTRL_ADDR);

	writel(SYNC_WR_TO_CH_ZERO, dp->regs + FIFO_CNTL);

	val = MAX_NUM_CH(audio->channels);
	val |= NUM_OF_I2S_PORTS(audio->channels);
	val |= AUDIO_TYPE_LPCM;
	val |= CFG_SUB_PCKT_NUM(sub_pckt_num);
	writel(val, dp->regs + SMPL2PKT_CNFG);

	if (audio->sample_width == 16)
		val = 0;
	else if (audio->sample_width == 24)
		val = 1 << 9;
	else
		val = 2 << 9;

	val |= AUDIO_CH_NUM(audio->channels);
	val |= I2S_DEC_PORT_EN(i2s_port_en_val);
	val |= TRANS_SMPL_WIDTH_32;
	writel(val, dp->regs + AUDIO_SRC_CNFG);

	for (i = 0; i < (audio->channels + 1) / 2; i++) {
		if (audio->sample_width == 16)
			val = (0x02 << 8) | (0x02 << 20);
		else if (audio->sample_width == 24)
			val = (0x0b << 8) | (0x0b << 20);

		val |= ((2 * i) << 4) | ((2 * i + 1) << 16);
		writel(val, dp->regs + STTS_BIT_CH(i));
	}

	switch (audio->sample_rate) {
	case 32000:
		val = SAMPLING_FREQ(3) |
		      ORIGINAL_SAMP_FREQ(0xc);
		break;
	case 44100:
		val = SAMPLING_FREQ(0) |
		      ORIGINAL_SAMP_FREQ(0xf);
		break;
	case 48000:
		val = SAMPLING_FREQ(2) |
		      ORIGINAL_SAMP_FREQ(0xd);
		break;
	case 88200:
		val = SAMPLING_FREQ(8) |
		      ORIGINAL_SAMP_FREQ(0x7);
		break;
	case 96000:
		val = SAMPLING_FREQ(0xa) |
		      ORIGINAL_SAMP_FREQ(5);
		break;
	case 176400:
		val = SAMPLING_FREQ(0xc) |
		      ORIGINAL_SAMP_FREQ(3);
		break;
	case 192000:
		val = SAMPLING_FREQ(0xe) |
		      ORIGINAL_SAMP_FREQ(1);
		break;
	}
	val |= 4;
	writel(val, dp->regs + COM_CH_STTS_BITS);

	writel(SMPL2PKT_EN, dp->regs + SMPL2PKT_CNTL);
	writel(I2S_DEC_START, dp->regs + AUDIO_SRC_CNTL);
}