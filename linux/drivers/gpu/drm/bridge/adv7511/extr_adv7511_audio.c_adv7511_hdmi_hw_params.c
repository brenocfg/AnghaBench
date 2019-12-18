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
struct hdmi_codec_params {int sample_rate; int sample_width; } ;
struct hdmi_codec_daifmt {int fmt; unsigned int bit_clk_inv; } ;
struct device {int dummy; } ;
struct adv7511 {unsigned int audio_source; int f_audio; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ADV7511_AUDIO_CFG3_LEN_MASK ; 
 unsigned int ADV7511_AUDIO_SOURCE_I2S ; 
 int ADV7511_I2C_FREQ_ID_CFG_RATE_MASK ; 
 unsigned int ADV7511_I2S_FORMAT_I2S ; 
 unsigned int ADV7511_I2S_FORMAT_LEFT_J ; 
 unsigned int ADV7511_I2S_FORMAT_RIGHT_J ; 
 unsigned int ADV7511_I2S_SAMPLE_LEN_16 ; 
 unsigned int ADV7511_I2S_SAMPLE_LEN_18 ; 
 unsigned int ADV7511_I2S_SAMPLE_LEN_20 ; 
 unsigned int ADV7511_I2S_SAMPLE_LEN_24 ; 
 int /*<<< orphan*/  ADV7511_REG_AUDIO_CFG3 ; 
 int /*<<< orphan*/  ADV7511_REG_AUDIO_CONFIG ; 
 int /*<<< orphan*/  ADV7511_REG_AUDIO_SOURCE ; 
 int /*<<< orphan*/  ADV7511_REG_I2C_FREQ_ID_CFG ; 
 int /*<<< orphan*/  ADV7511_REG_I2S_CONFIG ; 
 unsigned int ADV7511_SAMPLE_FREQ_176400 ; 
 unsigned int ADV7511_SAMPLE_FREQ_192000 ; 
 unsigned int ADV7511_SAMPLE_FREQ_32000 ; 
 unsigned int ADV7511_SAMPLE_FREQ_44100 ; 
 unsigned int ADV7511_SAMPLE_FREQ_48000 ; 
 unsigned int ADV7511_SAMPLE_FREQ_88200 ; 
 unsigned int ADV7511_SAMPLE_FREQ_96000 ; 
 int BIT (int) ; 
 int EINVAL ; 
#define  HDMI_I2S 130 
#define  HDMI_LEFT_J 129 
#define  HDMI_RIGHT_J 128 
 int /*<<< orphan*/  adv7511_update_cts_n (struct adv7511*) ; 
 struct adv7511* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 

int adv7511_hdmi_hw_params(struct device *dev, void *data,
			   struct hdmi_codec_daifmt *fmt,
			   struct hdmi_codec_params *hparms)
{
	struct adv7511 *adv7511 = dev_get_drvdata(dev);
	unsigned int audio_source, i2s_format = 0;
	unsigned int invert_clock;
	unsigned int rate;
	unsigned int len;

	switch (hparms->sample_rate) {
	case 32000:
		rate = ADV7511_SAMPLE_FREQ_32000;
		break;
	case 44100:
		rate = ADV7511_SAMPLE_FREQ_44100;
		break;
	case 48000:
		rate = ADV7511_SAMPLE_FREQ_48000;
		break;
	case 88200:
		rate = ADV7511_SAMPLE_FREQ_88200;
		break;
	case 96000:
		rate = ADV7511_SAMPLE_FREQ_96000;
		break;
	case 176400:
		rate = ADV7511_SAMPLE_FREQ_176400;
		break;
	case 192000:
		rate = ADV7511_SAMPLE_FREQ_192000;
		break;
	default:
		return -EINVAL;
	}

	switch (hparms->sample_width) {
	case 16:
		len = ADV7511_I2S_SAMPLE_LEN_16;
		break;
	case 18:
		len = ADV7511_I2S_SAMPLE_LEN_18;
		break;
	case 20:
		len = ADV7511_I2S_SAMPLE_LEN_20;
		break;
	case 24:
		len = ADV7511_I2S_SAMPLE_LEN_24;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt->fmt) {
	case HDMI_I2S:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_format = ADV7511_I2S_FORMAT_I2S;
		break;
	case HDMI_RIGHT_J:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_format = ADV7511_I2S_FORMAT_RIGHT_J;
		break;
	case HDMI_LEFT_J:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_format = ADV7511_I2S_FORMAT_LEFT_J;
		break;
	default:
		return -EINVAL;
	}

	invert_clock = fmt->bit_clk_inv;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_SOURCE, 0x70,
			   audio_source << 4);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG, BIT(6),
			   invert_clock << 6);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2S_CONFIG, 0x03,
			   i2s_format);

	adv7511->audio_source = audio_source;

	adv7511->f_audio = hparms->sample_rate;

	adv7511_update_cts_n(adv7511);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CFG3,
			   ADV7511_AUDIO_CFG3_LEN_MASK, len);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2C_FREQ_ID_CFG,
			   ADV7511_I2C_FREQ_ID_CFG_RATE_MASK, rate << 4);
	regmap_write(adv7511->regmap, 0x73, 0x1);

	return 0;
}