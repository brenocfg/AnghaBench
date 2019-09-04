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
struct v4l2_subdev_format {scalar_t__ which; int /*<<< orphan*/  pad; int /*<<< orphan*/  format; } ;
struct ov5670 {int /*<<< orphan*/  cur_mode; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  ov5670_update_pad_format (int /*<<< orphan*/ ,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/ * v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5670_do_get_pad_format(struct ov5670 *ov5670,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_format *fmt)
{
	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->format = *v4l2_subdev_get_try_format(&ov5670->sd, cfg,
							  fmt->pad);
	else
		ov5670_update_pad_format(ov5670->cur_mode, fmt);

	return 0;
}