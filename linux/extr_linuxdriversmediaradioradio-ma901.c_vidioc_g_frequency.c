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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct ma901radio_device {int /*<<< orphan*/  curfreq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ma901radio_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct ma901radio_device *radio = video_drvdata(file);

	if (f->tuner != 0)
		return -EINVAL;
	f->frequency = radio->curfreq;

	return 0;
}