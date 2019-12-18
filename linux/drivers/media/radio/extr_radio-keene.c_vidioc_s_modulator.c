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
struct v4l2_modulator {scalar_t__ index; scalar_t__ txsubchans; } ;
struct keene_device {int stereo; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_SUB_STEREO ; 
 int keene_cmd_set (struct keene_device*) ; 
 struct keene_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_modulator(struct file *file, void *priv,
				const struct v4l2_modulator *v)
{
	struct keene_device *radio = video_drvdata(file);

	if (v->index > 0)
		return -EINVAL;

	radio->stereo = (v->txsubchans == V4L2_TUNER_SUB_STEREO);
	return keene_cmd_set(radio);
}