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
struct ma901radio_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA901_WANT_MONO ; 
 int /*<<< orphan*/  MA901_WANT_STEREO ; 
#define  V4L2_TUNER_MODE_MONO 128 
 int ma901_set_stereo (struct ma901radio_device*,int /*<<< orphan*/ ) ; 
 struct ma901radio_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				const struct v4l2_tuner *v)
{
	struct ma901radio_device *radio = video_drvdata(file);

	if (v->index > 0)
		return -EINVAL;

	/* mono/stereo selector */
	switch (v->audmode) {
	case V4L2_TUNER_MODE_MONO:
		return ma901_set_stereo(radio, MA901_WANT_MONO);
	default:
		return ma901_set_stereo(radio, MA901_WANT_STEREO);
	}
}