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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; void* height; void* width; int /*<<< orphan*/  code; } ;
struct mt9v032 {TYPE_1__* model; } ;
struct TYPE_2__ {scalar_t__ color; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_Y10_1X10 ; 
 int /*<<< orphan*/  MT9V032_COLUMN_START_DEF ; 
 int /*<<< orphan*/  MT9V032_ROW_START_DEF ; 
 void* MT9V032_WINDOW_HEIGHT_DEF ; 
 void* MT9V032_WINDOW_WIDTH_DEF ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int mt9v032_set_power (struct v4l2_subdev*,int) ; 
 struct mt9v032* to_mt9v032 (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9v032_open(struct v4l2_subdev *subdev, struct v4l2_subdev_fh *fh)
{
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	crop = v4l2_subdev_get_try_crop(subdev, fh->pad, 0);
	crop->left = MT9V032_COLUMN_START_DEF;
	crop->top = MT9V032_ROW_START_DEF;
	crop->width = MT9V032_WINDOW_WIDTH_DEF;
	crop->height = MT9V032_WINDOW_HEIGHT_DEF;

	format = v4l2_subdev_get_try_format(subdev, fh->pad, 0);

	if (mt9v032->model->color)
		format->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	else
		format->code = MEDIA_BUS_FMT_Y10_1X10;

	format->width = MT9V032_WINDOW_WIDTH_DEF;
	format->height = MT9V032_WINDOW_HEIGHT_DEF;
	format->field = V4L2_FIELD_NONE;
	format->colorspace = V4L2_COLORSPACE_SRGB;

	return mt9v032_set_power(subdev, 1);
}