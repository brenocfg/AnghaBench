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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {scalar_t__ which; int /*<<< orphan*/  code; int /*<<< orphan*/  pad; scalar_t__ index; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

int xvip_enum_mbus_code(struct v4l2_subdev *subdev,
			struct v4l2_subdev_pad_config *cfg,
			struct v4l2_subdev_mbus_code_enum *code)
{
	struct v4l2_mbus_framefmt *format;

	/* Enumerating frame sizes based on the active configuration isn't
	 * supported yet.
	 */
	if (code->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return -EINVAL;

	if (code->index)
		return -EINVAL;

	format = v4l2_subdev_get_try_format(subdev, cfg, code->pad);

	code->code = format->code;

	return 0;
}