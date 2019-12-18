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
struct v4l2_tuner {scalar_t__ audmode; scalar_t__ index; } ;
struct pcm20 {scalar_t__ audmode; int /*<<< orphan*/  aci; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACI_SET_TUNERMONO ; 
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  snd_aci_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct pcm20* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				const struct v4l2_tuner *v)
{
	struct pcm20 *dev = video_drvdata(file);

	if (v->index)
		return -EINVAL;
	if (v->audmode > V4L2_TUNER_MODE_STEREO)
		dev->audmode = V4L2_TUNER_MODE_STEREO;
	else
		dev->audmode = v->audmode;
	snd_aci_cmd(dev->aci, ACI_SET_TUNERMONO,
			dev->audmode == V4L2_TUNER_MODE_MONO, -1);
	return 0;
}