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
typedef  int uint8_t ;
struct tm6000_core {scalar_t__ amode; int norm; scalar_t__ radio; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_08_SET_GET_AVREG_BIT ; 
 int /*<<< orphan*/  TM6010_REQ07_RFE_POWER_DOWN ; 
 int /*<<< orphan*/  TM6010_REQ08_R01_A_INIT ; 
 int /*<<< orphan*/  TM6010_REQ08_R02_A_FIX_GAIN_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_R03_A_AUTO_GAIN_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_R04_A_SIF_AMP_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_R05_A_STANDARD_MOD ; 
 int /*<<< orphan*/  TM6010_REQ08_R06_A_SOUND_MOD ; 
 int /*<<< orphan*/  TM6010_REQ08_R07_A_LEFT_VOL ; 
 int /*<<< orphan*/  TM6010_REQ08_R08_A_RIGHT_VOL ; 
 int /*<<< orphan*/  TM6010_REQ08_R09_A_MAIN_VOL ; 
 int /*<<< orphan*/  TM6010_REQ08_R0A_A_I2S_MOD ; 
 int /*<<< orphan*/  TM6010_REQ08_R0B_A_ASD_THRES1 ; 
 int /*<<< orphan*/  TM6010_REQ08_R0C_A_ASD_THRES2 ; 
 int /*<<< orphan*/  TM6010_REQ08_R0D_A_AMD_THRES ; 
 int /*<<< orphan*/  TM6010_REQ08_R0E_A_MONO_THRES1 ; 
 int /*<<< orphan*/  TM6010_REQ08_R0F_A_MONO_THRES2 ; 
 int /*<<< orphan*/  TM6010_REQ08_R10_A_MUTE_THRES1 ; 
 int /*<<< orphan*/  TM6010_REQ08_R11_A_MUTE_THRES2 ; 
 int /*<<< orphan*/  TM6010_REQ08_R12_A_AGC_U ; 
 int /*<<< orphan*/  TM6010_REQ08_R13_A_AGC_ERR_T ; 
 int /*<<< orphan*/  TM6010_REQ08_R14_A_AGC_GAIN_INIT ; 
 int /*<<< orphan*/  TM6010_REQ08_R15_A_AGC_STEP_THR ; 
 int /*<<< orphan*/  TM6010_REQ08_R16_A_AGC_GAIN_MAX ; 
 int /*<<< orphan*/  TM6010_REQ08_R17_A_AGC_GAIN_MIN ; 
 int /*<<< orphan*/  TM6010_REQ08_R18_A_TR_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_R19_A_FH_2FH_GAIN ; 
 int /*<<< orphan*/  TM6010_REQ08_R1A_A_NICAM_SER_MAX ; 
 int /*<<< orphan*/  TM6010_REQ08_R1B_A_NICAM_SER_MIN ; 
 int /*<<< orphan*/  TM6010_REQ08_R1E_A_GAIN_DEEMPH_OUT ; 
 int /*<<< orphan*/  TM6010_REQ08_R1F_A_TEST_INTF_SEL ; 
 int /*<<< orphan*/  TM6010_REQ08_R20_A_TEST_PIN_SEL ; 
 int /*<<< orphan*/  TM6010_REQ08_RF1_AADC_POWER_DOWN ; 
 int V4L2_STD_DK ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_NTSC_M_KR ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_SECAM_L ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int,...) ; 
 int tm6010_a_mode ; 

__attribute__((used)) static int tm6000_set_audio_std(struct tm6000_core *dev)
{
	uint8_t areg_02 = 0x04; /* GC1 Fixed gain 0dB */
	uint8_t areg_05 = 0x01; /* Auto 4.5 = M Japan, Auto 6.5 = DK */
	uint8_t areg_06 = 0x02; /* Auto de-emphasis, manual channel mode */

	if (dev->radio) {
		tm6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x00);
		tm6000_set_reg(dev, TM6010_REQ08_R02_A_FIX_GAIN_CTRL, 0x04);
		tm6000_set_reg(dev, TM6010_REQ08_R03_A_AUTO_GAIN_CTRL, 0x00);
		tm6000_set_reg(dev, TM6010_REQ08_R04_A_SIF_AMP_CTRL, 0x80);
		tm6000_set_reg(dev, TM6010_REQ08_R05_A_STANDARD_MOD, 0x0c);
		/* set mono or stereo */
		if (dev->amode == V4L2_TUNER_MODE_MONO)
			tm6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, 0x00);
		else if (dev->amode == V4L2_TUNER_MODE_STEREO)
			tm6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, 0x02);
		tm6000_set_reg(dev, TM6010_REQ08_R09_A_MAIN_VOL, 0x18);
		tm6000_set_reg(dev, TM6010_REQ08_R0C_A_ASD_THRES2, 0x0a);
		tm6000_set_reg(dev, TM6010_REQ08_R0D_A_AMD_THRES, 0x40);
		tm6000_set_reg(dev, TM6010_REQ08_RF1_AADC_POWER_DOWN, 0xfe);
		tm6000_set_reg(dev, TM6010_REQ08_R1E_A_GAIN_DEEMPH_OUT, 0x13);
		tm6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x80);
		tm6000_set_reg(dev, TM6010_REQ07_RFE_POWER_DOWN, 0xff);
		return 0;
	}

	/*
	 * STD/MN shouldn't be affected by tm6010_a_mode, as there's just one
	 * audio standard for each V4L2_STD type.
	 */
	if ((dev->norm & V4L2_STD_NTSC) == V4L2_STD_NTSC_M_KR) {
		areg_05 |= 0x04;
	} else if ((dev->norm & V4L2_STD_NTSC) == V4L2_STD_NTSC_M_JP) {
		areg_05 |= 0x43;
	} else if (dev->norm & V4L2_STD_MN) {
		areg_05 |= 0x22;
	} else switch (tm6010_a_mode) {
	/* auto */
	case 0:
		if ((dev->norm & V4L2_STD_SECAM) == V4L2_STD_SECAM_L)
			areg_05 |= 0x00;
		else	/* Other PAL/SECAM standards */
			areg_05 |= 0x10;
		break;
	/* A2 */
	case 1:
		if (dev->norm & V4L2_STD_DK)
			areg_05 = 0x09;
		else
			areg_05 = 0x05;
		break;
	/* NICAM */
	case 2:
		if (dev->norm & V4L2_STD_DK) {
			areg_05 = 0x06;
		} else if (dev->norm & V4L2_STD_PAL_I) {
			areg_05 = 0x08;
		} else if (dev->norm & V4L2_STD_SECAM_L) {
			areg_05 = 0x0a;
			areg_02 = 0x02;
		} else {
			areg_05 = 0x07;
		}
		break;
	/* other */
	case 3:
		if (dev->norm & V4L2_STD_DK) {
			areg_05 = 0x0b;
		} else {
			areg_05 = 0x02;
		}
		break;
	}

	tm6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R02_A_FIX_GAIN_CTRL, areg_02);
	tm6000_set_reg(dev, TM6010_REQ08_R03_A_AUTO_GAIN_CTRL, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R04_A_SIF_AMP_CTRL, 0xa0);
	tm6000_set_reg(dev, TM6010_REQ08_R05_A_STANDARD_MOD, areg_05);
	tm6000_set_reg(dev, TM6010_REQ08_R06_A_SOUND_MOD, areg_06);
	tm6000_set_reg(dev, TM6010_REQ08_R07_A_LEFT_VOL, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R08_A_RIGHT_VOL, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R09_A_MAIN_VOL, 0x08);
	tm6000_set_reg(dev, TM6010_REQ08_R0A_A_I2S_MOD, 0x91);
	tm6000_set_reg(dev, TM6010_REQ08_R0B_A_ASD_THRES1, 0x20);
	tm6000_set_reg(dev, TM6010_REQ08_R0C_A_ASD_THRES2, 0x12);
	tm6000_set_reg(dev, TM6010_REQ08_R0D_A_AMD_THRES, 0x20);
	tm6000_set_reg(dev, TM6010_REQ08_R0E_A_MONO_THRES1, 0xf0);
	tm6000_set_reg(dev, TM6010_REQ08_R0F_A_MONO_THRES2, 0x80);
	tm6000_set_reg(dev, TM6010_REQ08_R10_A_MUTE_THRES1, 0xc0);
	tm6000_set_reg(dev, TM6010_REQ08_R11_A_MUTE_THRES2, 0x80);
	tm6000_set_reg(dev, TM6010_REQ08_R12_A_AGC_U, 0x12);
	tm6000_set_reg(dev, TM6010_REQ08_R13_A_AGC_ERR_T, 0xfe);
	tm6000_set_reg(dev, TM6010_REQ08_R14_A_AGC_GAIN_INIT, 0x20);
	tm6000_set_reg(dev, TM6010_REQ08_R15_A_AGC_STEP_THR, 0x14);
	tm6000_set_reg(dev, TM6010_REQ08_R16_A_AGC_GAIN_MAX, 0xfe);
	tm6000_set_reg(dev, TM6010_REQ08_R17_A_AGC_GAIN_MIN, 0x01);
	tm6000_set_reg(dev, TM6010_REQ08_R18_A_TR_CTRL, 0xa0);
	tm6000_set_reg(dev, TM6010_REQ08_R19_A_FH_2FH_GAIN, 0x32);
	tm6000_set_reg(dev, TM6010_REQ08_R1A_A_NICAM_SER_MAX, 0x64);
	tm6000_set_reg(dev, TM6010_REQ08_R1B_A_NICAM_SER_MIN, 0x20);
	tm6000_set_reg(dev, REQ_08_SET_GET_AVREG_BIT, 0x1c, 0x00);
	tm6000_set_reg(dev, REQ_08_SET_GET_AVREG_BIT, 0x1d, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R1E_A_GAIN_DEEMPH_OUT, 0x13);
	tm6000_set_reg(dev, TM6010_REQ08_R1F_A_TEST_INTF_SEL, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R20_A_TEST_PIN_SEL, 0x00);
	tm6000_set_reg(dev, TM6010_REQ08_R01_A_INIT, 0x80);

	return 0;
}