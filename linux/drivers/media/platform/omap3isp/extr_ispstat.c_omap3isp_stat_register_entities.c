#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {TYPE_1__* mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct ispstat {TYPE_2__ subdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int v4l2_device_register_subdev (struct v4l2_device*,TYPE_2__*) ; 

int omap3isp_stat_register_entities(struct ispstat *stat,
				    struct v4l2_device *vdev)
{
	stat->subdev.dev = vdev->mdev->dev;

	return v4l2_device_register_subdev(vdev, &stat->subdev);
}