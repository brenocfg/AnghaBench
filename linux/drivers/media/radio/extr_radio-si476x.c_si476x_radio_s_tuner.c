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
struct v4l2_tuner {scalar_t__ index; scalar_t__ audmode; } ;
struct si476x_radio {scalar_t__ audmode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_s_tuner(struct file *file, void *priv,
				const struct v4l2_tuner *tuner)
{
	struct si476x_radio *radio = video_drvdata(file);

	if (tuner->index != 0)
		return -EINVAL;

	if (tuner->audmode == V4L2_TUNER_MODE_MONO ||
	    tuner->audmode == V4L2_TUNER_MODE_STEREO)
		radio->audmode = tuner->audmode;
	else
		radio->audmode = V4L2_TUNER_MODE_STEREO;

	return 0;
}