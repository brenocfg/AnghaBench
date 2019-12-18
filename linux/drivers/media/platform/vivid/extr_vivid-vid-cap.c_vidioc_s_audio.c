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
struct vivid_dev {scalar_t__ tv_audio_input; } ;
struct v4l2_audio {scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_audio_inputs ; 
 int /*<<< orphan*/  vivid_is_sdtv_cap (struct vivid_dev*) ; 

int vidioc_s_audio(struct file *file, void *fh, const struct v4l2_audio *vin)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_sdtv_cap(dev))
		return -EINVAL;
	if (vin->index >= ARRAY_SIZE(vivid_audio_inputs))
		return -EINVAL;
	dev->tv_audio_input = vin->index;
	return 0;
}