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
struct file {int dummy; } ;
struct amradio_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int amradio_set_freq (struct amradio_device*,int /*<<< orphan*/ ) ; 
 struct amradio_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				const struct v4l2_frequency *f)
{
	struct amradio_device *radio = video_drvdata(file);

	if (f->tuner != 0)
		return -EINVAL;
	return amradio_set_freq(radio, f->frequency);
}