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
struct v4l2_input {unsigned int index; int audioset; int /*<<< orphan*/  std; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDPVR_RCA_BACK ; 
 int HDPVR_RCA_FRONT ; 
 int HDPVR_SPDIF ; 
 unsigned int HDPVR_VIDEO_INPUTS ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/ * iname ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *_fh, struct v4l2_input *i)
{
	unsigned int n;

	n = i->index;
	if (n >= HDPVR_VIDEO_INPUTS)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[n], sizeof(i->name));

	i->audioset = 1<<HDPVR_RCA_FRONT | 1<<HDPVR_RCA_BACK | 1<<HDPVR_SPDIF;

	i->capabilities = n ? V4L2_IN_CAP_STD : V4L2_IN_CAP_DV_TIMINGS;
	i->std = n ? V4L2_STD_ALL : 0;

	return 0;
}