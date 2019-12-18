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
struct v4l2_output {int index; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOG ; 
 int /*<<< orphan*/  V4L2_OUT_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int cobalt_enum_output(struct file *file, void *priv_fh,
				 struct v4l2_output *out)
{
	if (out->index)
		return -EINVAL;
	snprintf(out->name, sizeof(out->name), "HDMI-%d", out->index);
	out->type = V4L2_OUTPUT_TYPE_ANALOG;
	out->capabilities = V4L2_OUT_CAP_DV_TIMINGS;
	return 0;
}