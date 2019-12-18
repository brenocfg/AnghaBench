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
struct v4l2_output {int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int vidioc_enum_output(struct file *file, void *priv_fh,
			      struct v4l2_output *out)
{
	if (out->index)
		return -EINVAL;
	snprintf(out->name, sizeof(out->name), "Overlay");
	out->type = V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY;
	return 0;
}