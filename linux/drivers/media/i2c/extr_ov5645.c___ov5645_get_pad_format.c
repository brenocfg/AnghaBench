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
struct v4l2_mbus_framefmt {int dummy; } ;
struct ov5645 {struct v4l2_mbus_framefmt fmt; int /*<<< orphan*/  sd; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
#define  V4L2_SUBDEV_FORMAT_ACTIVE 129 
#define  V4L2_SUBDEV_FORMAT_TRY 128 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
__ov5645_get_pad_format(struct ov5645 *ov5645,
			struct v4l2_subdev_pad_config *cfg,
			unsigned int pad,
			enum v4l2_subdev_format_whence which)
{
	switch (which) {
	case V4L2_SUBDEV_FORMAT_TRY:
		return v4l2_subdev_get_try_format(&ov5645->sd, cfg, pad);
	case V4L2_SUBDEV_FORMAT_ACTIVE:
		return &ov5645->fmt;
	default:
		return NULL;
	}
}