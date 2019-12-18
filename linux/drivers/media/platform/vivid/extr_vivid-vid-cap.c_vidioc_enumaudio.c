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
struct v4l2_audio {size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_audio*) ; 
 int EINVAL ; 
 struct v4l2_audio* vivid_audio_inputs ; 

int vidioc_enumaudio(struct file *file, void *fh, struct v4l2_audio *vin)
{
	if (vin->index >= ARRAY_SIZE(vivid_audio_inputs))
		return -EINVAL;
	*vin = vivid_audio_inputs[vin->index];
	return 0;
}