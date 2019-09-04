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
struct v4l2_rect {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5K6AA_OUT_HEIGHT_DEF ; 
 int /*<<< orphan*/  S5K6AA_OUT_WIDTH_DEF ; 
 int /*<<< orphan*/  S5K6AA_WIN_HEIGHT_MAX ; 
 int /*<<< orphan*/  S5K6AA_WIN_WIDTH_MAX ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_1__* s5k6aa_formats ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_open(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct v4l2_mbus_framefmt *format = v4l2_subdev_get_try_format(sd, fh->pad, 0);
	struct v4l2_rect *crop = v4l2_subdev_get_try_crop(sd, fh->pad, 0);

	format->colorspace = s5k6aa_formats[0].colorspace;
	format->code = s5k6aa_formats[0].code;
	format->width = S5K6AA_OUT_WIDTH_DEF;
	format->height = S5K6AA_OUT_HEIGHT_DEF;
	format->field = V4L2_FIELD_NONE;

	crop->width = S5K6AA_WIN_WIDTH_MAX;
	crop->height = S5K6AA_WIN_HEIGHT_MAX;
	crop->left = 0;
	crop->top = 0;

	return 0;
}