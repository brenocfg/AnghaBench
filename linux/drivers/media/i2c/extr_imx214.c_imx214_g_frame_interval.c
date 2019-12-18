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
struct TYPE_2__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_subdev_frame_interval {TYPE_1__ interval; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX214_FPS ; 

__attribute__((used)) static int imx214_g_frame_interval(struct v4l2_subdev *subdev,
				   struct v4l2_subdev_frame_interval *fival)
{
	fival->pad = 0;
	fival->interval.numerator = 1;
	fival->interval.denominator = IMX214_FPS;

	return 0;
}