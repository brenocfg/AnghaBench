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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAL_NUM_INPUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int cal_enum_input(struct file *file, void *priv,
			  struct v4l2_input *inp)
{
	if (inp->index >= CAL_NUM_INPUT)
		return -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	sprintf(inp->name, "Camera %u", inp->index);
	return 0;
}