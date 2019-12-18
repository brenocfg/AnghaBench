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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; void* height; void* width; int /*<<< orphan*/  code; } ;
struct mt9p031 {scalar_t__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_Y12_1X12 ; 
 int /*<<< orphan*/  MT9P031_COLUMN_START_DEF ; 
 scalar_t__ MT9P031_MODEL_MONOCHROME ; 
 int /*<<< orphan*/  MT9P031_ROW_START_DEF ; 
 void* MT9P031_WINDOW_HEIGHT_DEF ; 
 void* MT9P031_WINDOW_WIDTH_DEF ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int mt9p031_set_power (struct v4l2_subdev*,int) ; 
 struct mt9p031* to_mt9p031 (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9p031_open(struct v4l2_subdev *subdev, struct v4l2_subdev_fh *fh)
{
	struct mt9p031 *mt9p031 = to_mt9p031(subdev);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	crop = v4l2_subdev_get_try_crop(subdev, fh->pad, 0);
	crop->left = MT9P031_COLUMN_START_DEF;
	crop->top = MT9P031_ROW_START_DEF;
	crop->width = MT9P031_WINDOW_WIDTH_DEF;
	crop->height = MT9P031_WINDOW_HEIGHT_DEF;

	format = v4l2_subdev_get_try_format(subdev, fh->pad, 0);

	if (mt9p031->model == MT9P031_MODEL_MONOCHROME)
		format->code = MEDIA_BUS_FMT_Y12_1X12;
	else
		format->code = MEDIA_BUS_FMT_SGRBG12_1X12;

	format->width = MT9P031_WINDOW_WIDTH_DEF;
	format->height = MT9P031_WINDOW_HEIGHT_DEF;
	format->field = V4L2_FIELD_NONE;
	format->colorspace = V4L2_COLORSPACE_SRGB;

	return mt9p031_set_power(subdev, 1);
}