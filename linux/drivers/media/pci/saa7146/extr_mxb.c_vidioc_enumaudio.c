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
 int EINVAL ; 
 size_t MXB_AUDIOS ; 
 struct v4l2_audio* mxb_audios ; 

__attribute__((used)) static int vidioc_enumaudio(struct file *file, void *fh, struct v4l2_audio *a)
{
	if (a->index >= MXB_AUDIOS)
		return -EINVAL;
	*a = mxb_audios[a->index];
	return 0;
}