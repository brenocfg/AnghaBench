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
struct video_mux {struct v4l2_mbus_framefmt* format_mbus; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
#define  V4L2_SUBDEV_FORMAT_ACTIVE 129 
#define  V4L2_SUBDEV_FORMAT_TRY 128 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 
 struct video_mux* v4l2_subdev_to_video_mux (struct v4l2_subdev*) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
__video_mux_get_pad_format(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg,
			   unsigned int pad, u32 which)
{
	struct video_mux *vmux = v4l2_subdev_to_video_mux(sd);

	switch (which) {
	case V4L2_SUBDEV_FORMAT_TRY:
		return v4l2_subdev_get_try_format(sd, cfg, pad);
	case V4L2_SUBDEV_FORMAT_ACTIVE:
		return &vmux->format_mbus[pad];
	default:
		return NULL;
	}
}