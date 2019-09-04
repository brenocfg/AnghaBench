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
struct v4l2_subdev_fh {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void subdev_fh_free(struct v4l2_subdev_fh *fh)
{
#if defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	v4l2_subdev_free_pad_config(fh->pad);
	fh->pad = NULL;
#endif
}