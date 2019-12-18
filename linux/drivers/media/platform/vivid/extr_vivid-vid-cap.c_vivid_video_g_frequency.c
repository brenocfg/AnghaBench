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
struct vivid_dev {int /*<<< orphan*/  tv_freq; } ;
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_video_g_frequency(struct file *file, void *fh, struct v4l2_frequency *vf)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (vf->tuner != 0)
		return -EINVAL;
	vf->frequency = dev->tv_freq;
	return 0;
}