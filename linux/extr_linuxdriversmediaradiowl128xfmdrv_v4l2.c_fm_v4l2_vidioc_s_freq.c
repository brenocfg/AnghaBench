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
struct v4l2_frequency {int frequency; } ;
struct fmdev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int fmc_set_freq (struct fmdev*,int) ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_vidioc_s_freq(struct file *file, void *priv,
		const struct v4l2_frequency *freq)
{
	struct fmdev *fmdev = video_drvdata(file);

	/*
	 * As V4L2_TUNER_CAP_LOW is set 1 user sends the frequency
	 * in units of 62.5 Hz.
	 */
	return fmc_set_freq(fmdev, freq->frequency / 16);
}