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
struct TYPE_2__ {int /*<<< orphan*/  tuner_type; } ;
struct cx231xx {int /*<<< orphan*/  dev; TYPE_1__ board; } ;
typedef  enum AUDIO_INPUT { ____Placeholder_AUDIO_INPUT } AUDIO_INPUT ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CTL ; 
#define  AUDIO_INPUT_LINE 133 
#define  AUDIO_INPUT_MUTE 132 
#define  AUDIO_INPUT_TUNER_FM 131 
#define  AUDIO_INPUT_TUNER_TV 130 
 int AUD_CHAN_SRC_PARALLEL ; 
 int /*<<< orphan*/  AUD_IO_CTRL ; 
 int /*<<< orphan*/  BAND_OUT_SEL ; 
 int /*<<< orphan*/  CHIP_CTRL ; 
 int /*<<< orphan*/  DL_CTL ; 
 int /*<<< orphan*/  FLD_AC97_SRC_SEL ; 
 int FLD_AC97_UP2X_BYPASS ; 
 int /*<<< orphan*/  FLD_AUD_CHAN1_SRC ; 
 int /*<<< orphan*/  FLD_AUD_CHAN2_SRC ; 
 int /*<<< orphan*/  FLD_AUD_CHAN3_SRC ; 
 int /*<<< orphan*/  FLD_BASEBAND_BYPASS_CTL ; 
 int /*<<< orphan*/  FLD_I2S_OUT_SRC ; 
 int /*<<< orphan*/  FLD_I2S_PORT_DIR ; 
 int /*<<< orphan*/  FLD_I2S_SRC_SEL ; 
 int /*<<< orphan*/  FLD_PARALLEL1_SRC_SEL ; 
 int /*<<< orphan*/  FLD_PARALLEL2_SRC_SEL ; 
 int FLD_PATH1_AVC_THRESHOLD ; 
 int FLD_PATH1_SC_THRESHOLD ; 
 int /*<<< orphan*/  FLD_SIF_EN ; 
 int /*<<< orphan*/  FLD_SRC3_CLK_SEL ; 
 int /*<<< orphan*/  FLD_SRC3_IN_SEL ; 
 int /*<<< orphan*/  FLD_SRC4_CLK_SEL ; 
 int /*<<< orphan*/  FLD_SRC4_IN_SEL ; 
 int /*<<< orphan*/  FLD_SRC5_CLK_SEL ; 
 int /*<<< orphan*/  FLD_SRC5_IN_SEL ; 
 int /*<<< orphan*/  FLD_SRC6_CLK_SEL ; 
 int /*<<< orphan*/  FLD_SRC6_IN_SEL ; 
 int /*<<< orphan*/  GENERAL_CTL ; 
 int /*<<< orphan*/  PATH1_CTL1 ; 
 int /*<<< orphan*/  PATH1_SC_CTL ; 
 int /*<<< orphan*/  PATH1_VOL_CTL ; 
#define  TUNER_NXP_TDA18271 129 
#define  TUNER_XC5000 128 
 int /*<<< orphan*/  VID_BLK_I2C_ADDRESS ; 
 int cx231xx_read_modify_write_i2c_dword (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cx231xx_set_field (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int restartAudioFirmware (struct cx231xx*) ; 
 int stopAudioFirmware (struct cx231xx*) ; 
 int vid_blk_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int vid_blk_read_word (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int vid_blk_write_byte (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int vid_blk_write_word (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

int cx231xx_set_audio_decoder_input(struct cx231xx *dev,
				    enum AUDIO_INPUT audio_input)
{
	u32 dwval;
	int status;
	u8 gen_ctrl;
	u32 value = 0;

	/* Put it in soft reset   */
	status = vid_blk_read_byte(dev, GENERAL_CTL, &gen_ctrl);
	gen_ctrl |= 1;
	status = vid_blk_write_byte(dev, GENERAL_CTL, gen_ctrl);

	switch (audio_input) {
	case AUDIO_INPUT_LINE:
		/* setup AUD_IO control from Merlin paralle output */
		value = cx231xx_set_field(FLD_AUD_CHAN1_SRC,
					  AUD_CHAN_SRC_PARALLEL);
		status = vid_blk_write_word(dev, AUD_IO_CTRL, value);

		/* setup input to Merlin, SRC2 connect to AC97
		   bypass upsample-by-2, slave mode, sony mode, left justify
		   adr 091c, dat 01000000 */
		status = vid_blk_read_word(dev, AC97_CTL, &dwval);

		status = vid_blk_write_word(dev, AC97_CTL,
					   (dwval | FLD_AC97_UP2X_BYPASS));

		/* select the parallel1 and SRC3 */
		status = vid_blk_write_word(dev, BAND_OUT_SEL,
				cx231xx_set_field(FLD_SRC3_IN_SEL, 0x0) |
				cx231xx_set_field(FLD_SRC3_CLK_SEL, 0x0) |
				cx231xx_set_field(FLD_PARALLEL1_SRC_SEL, 0x0));

		/* unmute all, AC97 in, independence mode
		   adr 08d0, data 0x00063073 */
		status = vid_blk_write_word(dev, DL_CTL, 0x3000001);
		status = vid_blk_write_word(dev, PATH1_CTL1, 0x00063073);

		/* set AVC maximum threshold, adr 08d4, dat ffff0024 */
		status = vid_blk_read_word(dev, PATH1_VOL_CTL, &dwval);
		status = vid_blk_write_word(dev, PATH1_VOL_CTL,
					   (dwval | FLD_PATH1_AVC_THRESHOLD));

		/* set SC maximum threshold, adr 08ec, dat ffffb3a3 */
		status = vid_blk_read_word(dev, PATH1_SC_CTL, &dwval);
		status = vid_blk_write_word(dev, PATH1_SC_CTL,
					   (dwval | FLD_PATH1_SC_THRESHOLD));
		break;

	case AUDIO_INPUT_TUNER_TV:
	default:
		status = stopAudioFirmware(dev);
		/* Setup SRC sources and clocks */
		status = vid_blk_write_word(dev, BAND_OUT_SEL,
			cx231xx_set_field(FLD_SRC6_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC6_CLK_SEL, 0x01)        |
			cx231xx_set_field(FLD_SRC5_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC5_CLK_SEL, 0x02)        |
			cx231xx_set_field(FLD_SRC4_IN_SEL, 0x02)         |
			cx231xx_set_field(FLD_SRC4_CLK_SEL, 0x03)        |
			cx231xx_set_field(FLD_SRC3_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC3_CLK_SEL, 0x00)        |
			cx231xx_set_field(FLD_BASEBAND_BYPASS_CTL, 0x00) |
			cx231xx_set_field(FLD_AC97_SRC_SEL, 0x03)        |
			cx231xx_set_field(FLD_I2S_SRC_SEL, 0x00)         |
			cx231xx_set_field(FLD_PARALLEL2_SRC_SEL, 0x02)   |
			cx231xx_set_field(FLD_PARALLEL1_SRC_SEL, 0x01));

		/* Setup the AUD_IO control */
		status = vid_blk_write_word(dev, AUD_IO_CTRL,
			cx231xx_set_field(FLD_I2S_PORT_DIR, 0x00)  |
			cx231xx_set_field(FLD_I2S_OUT_SRC, 0x00)   |
			cx231xx_set_field(FLD_AUD_CHAN3_SRC, 0x00) |
			cx231xx_set_field(FLD_AUD_CHAN2_SRC, 0x00) |
			cx231xx_set_field(FLD_AUD_CHAN1_SRC, 0x03));

		status = vid_blk_write_word(dev, PATH1_CTL1, 0x1F063870);

		/* setAudioStandard(_audio_standard); */
		status = vid_blk_write_word(dev, PATH1_CTL1, 0x00063870);

		status = restartAudioFirmware(dev);

		switch (dev->board.tuner_type) {
		case TUNER_XC5000:
			/* SIF passthrough at 28.6363 MHz sample rate */
			status = cx231xx_read_modify_write_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					CHIP_CTRL,
					FLD_SIF_EN,
					cx231xx_set_field(FLD_SIF_EN, 1));
			break;
		case TUNER_NXP_TDA18271:
			/* Normal mode: SIF passthrough at 14.32 MHz */
			status = cx231xx_read_modify_write_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					CHIP_CTRL,
					FLD_SIF_EN,
					cx231xx_set_field(FLD_SIF_EN, 0));
			break;
		default:
			/* This is just a casual suggestion to people adding
			   new boards in case they use a tuner type we don't
			   currently know about */
			dev_info(dev->dev,
				 "Unknown tuner type configuring SIF");
			break;
		}
		break;

	case AUDIO_INPUT_TUNER_FM:
		/*  use SIF for FM radio
		   setupFM();
		   setAudioStandard(_audio_standard);
		 */
		break;

	case AUDIO_INPUT_MUTE:
		status = vid_blk_write_word(dev, PATH1_CTL1, 0x1F011012);
		break;
	}

	/* Take it out of soft reset */
	status = vid_blk_read_byte(dev, GENERAL_CTL, &gen_ctrl);
	gen_ctrl &= ~1;
	status = vid_blk_write_byte(dev, GENERAL_CTL, gen_ctrl);

	return status;
}