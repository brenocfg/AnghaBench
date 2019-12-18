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
struct v4l2_input {int index; scalar_t__ status; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dt3155_enum_input(struct file *filp, void *p,
			     struct v4l2_input *input)
{
	if (input->index > 3)
		return -EINVAL;
	if (input->index)
		snprintf(input->name, sizeof(input->name), "VID%d",
			 input->index);
	else
		strscpy(input->name, "J2/VID0", sizeof(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = V4L2_STD_ALL;
	input->status = 0;
	return 0;
}