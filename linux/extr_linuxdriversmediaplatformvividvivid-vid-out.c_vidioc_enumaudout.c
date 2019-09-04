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
struct v4l2_audioout {size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_audioout*) ; 
 int EINVAL ; 
 struct v4l2_audioout* vivid_audio_outputs ; 

int vidioc_enumaudout(struct file *file, void *fh, struct v4l2_audioout *vout)
{
	if (vout->index >= ARRAY_SIZE(vivid_audio_outputs))
		return -EINVAL;
	*vout = vivid_audio_outputs[vout->index];
	return 0;
}