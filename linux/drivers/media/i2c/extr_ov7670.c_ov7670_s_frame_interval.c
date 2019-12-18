#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fract {int dummy; } ;
struct v4l2_subdev_frame_interval {struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;
struct ov7670_info {TYPE_1__* devtype; } ;
struct TYPE_2__ {int (* set_framerate ) (struct v4l2_subdev*,struct v4l2_fract*) ;} ;

/* Variables and functions */
 int stub1 (struct v4l2_subdev*,struct v4l2_fract*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *ival)
{
	struct v4l2_fract *tpf = &ival->interval;
	struct ov7670_info *info = to_state(sd);


	return info->devtype->set_framerate(sd, tpf);
}