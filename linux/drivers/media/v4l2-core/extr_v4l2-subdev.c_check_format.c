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
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_cfg (int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*) ; 
 scalar_t__ check_pad (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_which (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_format(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_format *format)
{
	if (!format)
		return -EINVAL;

	return check_which(format->which) ? : check_pad(sd, format->pad) ? :
	       check_cfg(format->which, cfg);
}