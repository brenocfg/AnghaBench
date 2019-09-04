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
struct v4l2_device {int dummy; } ;
struct ispstat {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int v4l2_device_register_subdev (struct v4l2_device*,int /*<<< orphan*/ *) ; 

int omap3isp_stat_register_entities(struct ispstat *stat,
				    struct v4l2_device *vdev)
{
	return v4l2_device_register_subdev(vdev, &stat->subdev);
}