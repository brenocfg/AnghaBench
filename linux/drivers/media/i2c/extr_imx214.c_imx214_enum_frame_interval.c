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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_subdev_frame_interval_enum {scalar_t__ index; TYPE_1__ interval; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev {int dummy; } ;
struct imx214_mode {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IMX214_FPS ; 
 int /*<<< orphan*/  IMX214_MBUS_CODE ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  imx214_modes ; 
 struct imx214_mode* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static int imx214_enum_frame_interval(struct v4l2_subdev *subdev,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_interval_enum *fie)
{
	const struct imx214_mode *mode;

	if (fie->index != 0)
		return -EINVAL;

	mode = v4l2_find_nearest_size(imx214_modes,
				ARRAY_SIZE(imx214_modes), width, height,
				fie->width, fie->height);

	fie->code = IMX214_MBUS_CODE;
	fie->width = mode->width;
	fie->height = mode->height;
	fie->interval.numerator = 1;
	fie->interval.denominator = IMX214_FPS;

	return 0;
}