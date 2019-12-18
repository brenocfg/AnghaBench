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
struct v4l2_input {size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,size_t) ; 
 int EINVAL ; 
 size_t MXB_INPUTS ; 
 int /*<<< orphan*/  memcpy (struct v4l2_input*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mxb_inputs ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *fh, struct v4l2_input *i)
{
	DEB_EE("VIDIOC_ENUMINPUT %d\n", i->index);
	if (i->index >= MXB_INPUTS)
		return -EINVAL;
	memcpy(i, &mxb_inputs[i->index], sizeof(struct v4l2_input));
	return 0;
}