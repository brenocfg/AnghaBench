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
typedef  int u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct mt9p031 {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
#define  V4L2_SUBDEV_FORMAT_ACTIVE 129 
#define  V4L2_SUBDEV_FORMAT_TRY 128 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
__mt9p031_get_pad_format(struct mt9p031 *mt9p031, struct v4l2_subdev_pad_config *cfg,
			 unsigned int pad, u32 which)
{
	switch (which) {
	case V4L2_SUBDEV_FORMAT_TRY:
		return v4l2_subdev_get_try_format(&mt9p031->subdev, cfg, pad);
	case V4L2_SUBDEV_FORMAT_ACTIVE:
		return &mt9p031->format;
	default:
		return NULL;
	}
}