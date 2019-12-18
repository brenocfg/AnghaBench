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
struct v4l2_tuner {scalar_t__ index; int capability; int signal; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct saa7134_dev {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int SAA7134_INPUT_MAX ; 
 scalar_t__ SAA7134_INPUT_TV ; 
 scalar_t__ SAA7134_INPUT_TV_MONO ; 
 scalar_t__ SAA7134_NO_INPUT ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_NORM ; 
 int V4L2_TUNER_CAP_STEREO ; 
 TYPE_1__ card_in (struct saa7134_dev*,int) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7134_tvaudio_getstereo (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_rx2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

int saa7134_g_tuner(struct file *file, void *priv,
					struct v4l2_tuner *t)
{
	struct saa7134_dev *dev = video_drvdata(file);
	int n;

	if (0 != t->index)
		return -EINVAL;
	memset(t, 0, sizeof(*t));
	for (n = 0; n < SAA7134_INPUT_MAX; n++) {
		if (card_in(dev, n).type == SAA7134_INPUT_TV ||
		    card_in(dev, n).type == SAA7134_INPUT_TV_MONO)
			break;
	}
	if (n == SAA7134_INPUT_MAX)
		return -EINVAL;
	if (card_in(dev, n).type != SAA7134_NO_INPUT) {
		strscpy(t->name, "Television", sizeof(t->name));
		t->type = V4L2_TUNER_ANALOG_TV;
		saa_call_all(dev, tuner, g_tuner, t);
		t->capability = V4L2_TUNER_CAP_NORM |
			V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_LANG1 |
			V4L2_TUNER_CAP_LANG2;
		t->rxsubchans = saa7134_tvaudio_getstereo(dev);
		t->audmode = saa7134_tvaudio_rx2mode(t->rxsubchans);
	}
	if (0 != (saa_readb(SAA7134_STATUS_VIDEO1) & 0x03))
		t->signal = 0xffff;
	return 0;
}