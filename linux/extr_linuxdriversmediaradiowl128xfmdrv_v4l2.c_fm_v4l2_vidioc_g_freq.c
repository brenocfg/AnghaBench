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
typedef  int u32 ;
struct v4l2_frequency {int frequency; } ;
struct fmdev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int fmc_get_freq (struct fmdev*,int*) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 struct fmdev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fm_v4l2_vidioc_g_freq(struct file *file, void *priv,
		struct v4l2_frequency *freq)
{
	struct fmdev *fmdev = video_drvdata(file);
	int ret;

	ret = fmc_get_freq(fmdev, &freq->frequency);
	if (ret < 0) {
		fmerr("Failed to get frequency\n");
		return ret;
	}

	/* Frequency unit of 62.5 Hz*/
	freq->frequency = (u32) freq->frequency * 16;

	return 0;
}