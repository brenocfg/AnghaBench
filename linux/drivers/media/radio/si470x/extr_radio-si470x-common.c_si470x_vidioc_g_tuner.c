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
struct v4l2_tuner {scalar_t__ index; int capability; int rangelow; int rangehigh; int signal; int afc; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct si470x_device {int (* get_register ) (struct si470x_device*,size_t) ;int* registers; int /*<<< orphan*/  status_rssi_auto_update; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_MUL ; 
 size_t POWERCFG ; 
 int POWERCFG_MONO ; 
 size_t STATUSRSSI ; 
 int STATUSRSSI_AFCRL ; 
 int STATUSRSSI_RSSI ; 
 int STATUSRSSI_ST ; 
 int V4L2_TUNER_CAP_HWSEEK_BOUNDED ; 
 int V4L2_TUNER_CAP_HWSEEK_WRAP ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_RDS_BLOCK_IO ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_RDS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct si470x_device*,size_t) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_g_tuner(struct file *file, void *priv,
		struct v4l2_tuner *tuner)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = 0;

	if (tuner->index != 0)
		return -EINVAL;

	if (!radio->status_rssi_auto_update) {
		retval = radio->get_register(radio, STATUSRSSI);
		if (retval < 0)
			return retval;
	}

	/* driver constants */
	strscpy(tuner->name, "FM", sizeof(tuner->name));
	tuner->type = V4L2_TUNER_RADIO;
	tuner->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			    V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO |
			    V4L2_TUNER_CAP_HWSEEK_BOUNDED |
			    V4L2_TUNER_CAP_HWSEEK_WRAP;
	tuner->rangelow  =  76 * FREQ_MUL;
	tuner->rangehigh = 108 * FREQ_MUL;

	/* stereo indicator == stereo (instead of mono) */
	if ((radio->registers[STATUSRSSI] & STATUSRSSI_ST) == 0)
		tuner->rxsubchans = V4L2_TUNER_SUB_MONO;
	else
		tuner->rxsubchans = V4L2_TUNER_SUB_STEREO;
	/* If there is a reliable method of detecting an RDS channel,
	   then this code should check for that before setting this
	   RDS subchannel. */
	tuner->rxsubchans |= V4L2_TUNER_SUB_RDS;

	/* mono/stereo selector */
	if ((radio->registers[POWERCFG] & POWERCFG_MONO) == 0)
		tuner->audmode = V4L2_TUNER_MODE_STEREO;
	else
		tuner->audmode = V4L2_TUNER_MODE_MONO;

	/* min is worst, max is best; signal:0..0xffff; rssi: 0..0xff */
	/* measured in units of dbµV in 1 db increments (max at ~75 dbµV) */
	tuner->signal = (radio->registers[STATUSRSSI] & STATUSRSSI_RSSI);
	/* the ideal factor is 0xffff/75 = 873,8 */
	tuner->signal = (tuner->signal * 873) + (8 * tuner->signal / 10);
	if (tuner->signal > 0xffff)
		tuner->signal = 0xffff;

	/* automatic frequency control: -1: freq to low, 1 freq to high */
	/* AFCRL does only indicate that freq. differs, not if too low/high */
	tuner->afc = (radio->registers[STATUSRSSI] & STATUSRSSI_AFCRL) ? 1 : 0;

	return retval;
}