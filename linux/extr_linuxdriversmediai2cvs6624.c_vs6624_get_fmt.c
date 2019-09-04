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
struct vs6624 {int /*<<< orphan*/  fmt; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vs6624* to_vs6624 (struct v4l2_subdev*) ; 

__attribute__((used)) static int vs6624_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct vs6624 *sensor = to_vs6624(sd);

	if (format->pad)
		return -EINVAL;

	format->format = sensor->fmt;
	return 0;
}