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
struct v4l2_input {int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25821_NORMS ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cx25821_vidioc_enum_input(struct file *file, void *priv,
			      struct v4l2_input *i)
{
	if (i->index)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = CX25821_NORMS;
	strscpy(i->name, "Composite", sizeof(i->name));
	return 0;
}