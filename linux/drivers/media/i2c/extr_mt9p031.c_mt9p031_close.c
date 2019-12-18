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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int mt9p031_set_power (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9p031_close(struct v4l2_subdev *subdev, struct v4l2_subdev_fh *fh)
{
	return mt9p031_set_power(subdev, 0);
}