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
struct v4l2_input {scalar_t__ index; scalar_t__ capabilities; int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TOUCH ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sur40_vidioc_enum_input(struct file *file, void *priv,
				   struct v4l2_input *i)
{
	if (i->index != 0)
		return -EINVAL;
	i->type = V4L2_INPUT_TYPE_TOUCH;
	i->std = V4L2_STD_UNKNOWN;
	strlcpy(i->name, "In-Cell Sensor", sizeof(i->name));
	i->capabilities = 0;
	return 0;
}