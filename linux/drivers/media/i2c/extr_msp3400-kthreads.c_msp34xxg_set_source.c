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
typedef  int /*<<< orphan*/  u16 ;
struct msp_state {int audmode; scalar_t__ has_dolby_pro_logic; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MSP_DSP_IN_MAIN_AVC ; 
 int MSP_DSP_IN_TUNER ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_write_dsp (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msp34xxg_set_source(struct i2c_client *client, u16 reg, int in)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int source, matrix;

	switch (state->audmode) {
	case V4L2_TUNER_MODE_MONO:
		source = 0; /* mono only */
		matrix = 0x30;
		break;
	case V4L2_TUNER_MODE_LANG2:
		source = 4; /* stereo or B */
		matrix = 0x10;
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		source = 1; /* stereo or A|B */
		matrix = 0x20;
		break;
	case V4L2_TUNER_MODE_LANG1:
		source = 3; /* stereo or A */
		matrix = 0x00;
		break;
	case V4L2_TUNER_MODE_STEREO:
	default:
		source = 3; /* stereo or A */
		matrix = 0x20;
		break;
	}

	if (in == MSP_DSP_IN_TUNER)
		source = (source << 8) | 0x20;
	/* the msp34x2g puts the MAIN_AVC, MAIN and AUX sources in 12, 13, 14
	   instead of 11, 12, 13. So we add one for that msp version. */
	else if (in >= MSP_DSP_IN_MAIN_AVC && state->has_dolby_pro_logic)
		source = ((in + 1) << 8) | matrix;
	else
		source = (in << 8) | matrix;

	dev_dbg_lvl(&client->dev, 1, msp_debug,
		"set source to %d (0x%x) for output %02x\n", in, source, reg);
	msp_write_dsp(client, reg, source);
}