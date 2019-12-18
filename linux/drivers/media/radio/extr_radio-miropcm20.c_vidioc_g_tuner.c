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
typedef  scalar_t__ u8 ;
struct v4l2_tuner {int rangelow; int rangehigh; int signal; int capability; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct pcm20 {int /*<<< orphan*/  aci; int /*<<< orphan*/  audmode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACI_READ_TUNERSTATION ; 
 int /*<<< orphan*/  ACI_READ_TUNERSTEREO ; 
 int EINVAL ; 
 int /*<<< orphan*/  RDS_RXVALUE ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_RDS_CONTROLS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_RDS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int rds_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int snd_aci_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct pcm20* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
				struct v4l2_tuner *v)
{
	struct pcm20 *dev = video_drvdata(file);
	int res;
	u8 buf;

	if (v->index)
		return -EINVAL;
	strscpy(v->name, "FM", sizeof(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = 87*16000;
	v->rangehigh = 108*16000;
	res = snd_aci_cmd(dev->aci, ACI_READ_TUNERSTATION, -1, -1);
	v->signal = (res & 0x80) ? 0 : 0xffff;
	/* Note: stereo detection does not work if the audio is muted,
	   it will default to mono in that case. */
	res = snd_aci_cmd(dev->aci, ACI_READ_TUNERSTEREO, -1, -1);
	v->rxsubchans = (res & 0x40) ? V4L2_TUNER_SUB_MONO :
					V4L2_TUNER_SUB_STEREO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_CONTROLS;
	v->audmode = dev->audmode;
	res = rds_cmd(dev->aci, RDS_RXVALUE, &buf, 1);
	if (res >= 0 && buf)
		v->rxsubchans |= V4L2_TUNER_SUB_RDS;
	return 0;
}