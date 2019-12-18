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
struct msp_state {int rxsubchans; int nicam_on; int mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  MSP_MODE_AM_NICAM 131 
#define  MSP_MODE_FM_NICAM1 130 
#define  MSP_MODE_FM_NICAM2 129 
#define  MSP_MODE_FM_TERRA 128 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 int msp_read_dem (struct i2c_client*,int) ; 
 int msp_read_dsp (struct i2c_client*,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msp3400c_detect_stereo(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int val;
	int rxsubchans = state->rxsubchans;
	int newnicam = state->nicam_on;
	int update = 0;

	switch (state->mode) {
	case MSP_MODE_FM_TERRA:
		val = msp_read_dsp(client, 0x18);
		if (val > 32767)
			val -= 65536;
		dev_dbg_lvl(&client->dev, 2, msp_debug,
			"stereo detect register: %d\n", val);
		if (val > 8192) {
			rxsubchans = V4L2_TUNER_SUB_STEREO;
		} else if (val < -4096) {
			rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		} else {
			rxsubchans = V4L2_TUNER_SUB_MONO;
		}
		newnicam = 0;
		break;
	case MSP_MODE_FM_NICAM1:
	case MSP_MODE_FM_NICAM2:
	case MSP_MODE_AM_NICAM:
		val = msp_read_dem(client, 0x23);
		dev_dbg_lvl(&client->dev, 2, msp_debug, "nicam sync=%d, mode=%d\n",
			val & 1, (val & 0x1e) >> 1);

		if (val & 1) {
			/* nicam synced */
			switch ((val & 0x1e) >> 1)  {
			case 0:
			case 8:
				rxsubchans = V4L2_TUNER_SUB_STEREO;
				break;
			case 1:
			case 9:
				rxsubchans = V4L2_TUNER_SUB_MONO;
				break;
			case 2:
			case 10:
				rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
				break;
			default:
				rxsubchans = V4L2_TUNER_SUB_MONO;
				break;
			}
			newnicam = 1;
		} else {
			newnicam = 0;
			rxsubchans = V4L2_TUNER_SUB_MONO;
		}
		break;
	}
	if (rxsubchans != state->rxsubchans) {
		update = 1;
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"watch: rxsubchans %02x => %02x\n",
			state->rxsubchans, rxsubchans);
		state->rxsubchans = rxsubchans;
	}
	if (newnicam != state->nicam_on) {
		update = 1;
		dev_dbg_lvl(&client->dev, 1, msp_debug, "watch: nicam %d => %d\n",
			state->nicam_on, newnicam);
		state->nicam_on = newnicam;
	}
	return update;
}