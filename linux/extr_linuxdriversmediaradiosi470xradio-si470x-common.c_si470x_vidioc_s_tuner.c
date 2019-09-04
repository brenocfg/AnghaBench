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
struct v4l2_tuner {scalar_t__ index; int audmode; } ;
struct si470x_device {int (* set_register ) (struct si470x_device*,size_t) ;int /*<<< orphan*/ * registers; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t POWERCFG ; 
 int /*<<< orphan*/  POWERCFG_MONO ; 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int stub1 (struct si470x_device*,size_t) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_s_tuner(struct file *file, void *priv,
		const struct v4l2_tuner *tuner)
{
	struct si470x_device *radio = video_drvdata(file);

	if (tuner->index != 0)
		return -EINVAL;

	/* mono/stereo selector */
	switch (tuner->audmode) {
	case V4L2_TUNER_MODE_MONO:
		radio->registers[POWERCFG] |= POWERCFG_MONO;  /* force mono */
		break;
	case V4L2_TUNER_MODE_STEREO:
	default:
		radio->registers[POWERCFG] &= ~POWERCFG_MONO; /* try stereo */
		break;
	}

	return radio->set_register(radio, POWERCFG);
}