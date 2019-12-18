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
struct v4l2_subdev_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int tvp7002_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int
tvp7002_set_pad_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_format *fmt)
{
	return tvp7002_get_pad_format(sd, cfg, fmt);
}