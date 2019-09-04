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
typedef  scalar_t__ u32 ;
struct v4l2_tuner {scalar_t__ audmode; scalar_t__ index; } ;
struct radio_tea5777 {scalar_t__ audmode; scalar_t__ band; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_FM ; 
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int radio_tea5777_set_freq (struct radio_tea5777*) ; 
 struct radio_tea5777* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
					const struct v4l2_tuner *v)
{
	struct radio_tea5777 *tea = video_drvdata(file);
	u32 orig_audmode = tea->audmode;

	if (v->index)
		return -EINVAL;

	tea->audmode = v->audmode;
	if (tea->audmode > V4L2_TUNER_MODE_STEREO)
		tea->audmode = V4L2_TUNER_MODE_STEREO;

	if (tea->audmode != orig_audmode && tea->band == BAND_FM)
		return radio_tea5777_set_freq(tea);

	return 0;
}