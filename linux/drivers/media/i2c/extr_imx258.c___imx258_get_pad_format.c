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
struct imx258 {int /*<<< orphan*/  cur_mode; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  imx258_update_pad_format (int /*<<< orphan*/ ,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/ * v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __imx258_get_pad_format(struct imx258 *imx258,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_format *fmt)
{
	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->format = *v4l2_subdev_get_try_format(&imx258->sd, cfg,
							  fmt->pad);
	else
		imx258_update_pad_format(imx258->cur_mode, fmt);

	return 0;
}