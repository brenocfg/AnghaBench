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
struct v4l2_rect {scalar_t__ height; scalar_t__ width; void* top; void* left; } ;
struct v4l2_subdev_selection {scalar_t__ which; scalar_t__ target; struct v4l2_rect r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9m111 {int width; int height; struct v4l2_rect rect; TYPE_1__* fmt; } ;
struct i2c_client {int dummy; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_2__ {scalar_t__ code; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 scalar_t__ MT9M111_MAX_HEIGHT ; 
 scalar_t__ MT9M111_MAX_WIDTH ; 
 scalar_t__ MT9M111_MIN_DARK_COLS ; 
 scalar_t__ MT9M111_MIN_DARK_ROWS ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 void* clamp (void*,scalar_t__,scalar_t__) ; 
 int min (int,scalar_t__) ; 
 int mt9m111_setup_geometry (struct mt9m111*,struct v4l2_rect*,int,int,scalar_t__) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int,scalar_t__,int,scalar_t__*,int,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9m111_set_selection(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_selection *sel)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	struct v4l2_rect rect = sel->r;
	int width, height;
	int ret, align = 0;

	if (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	if (mt9m111->fmt->code == MEDIA_BUS_FMT_SBGGR8_1X8 ||
	    mt9m111->fmt->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) {
		/* Bayer format - even size lengths */
		align = 1;
		/* Let the user play with the starting pixel */
	}

	/* FIXME: the datasheet doesn't specify minimum sizes */
	v4l_bound_align_image(&rect.width, 2, MT9M111_MAX_WIDTH, align,
			      &rect.height, 2, MT9M111_MAX_HEIGHT, align, 0);
	rect.left = clamp(rect.left, MT9M111_MIN_DARK_COLS,
			  MT9M111_MIN_DARK_COLS + MT9M111_MAX_WIDTH -
			  (__s32)rect.width);
	rect.top = clamp(rect.top, MT9M111_MIN_DARK_ROWS,
			 MT9M111_MIN_DARK_ROWS + MT9M111_MAX_HEIGHT -
			 (__s32)rect.height);

	width = min(mt9m111->width, rect.width);
	height = min(mt9m111->height, rect.height);

	ret = mt9m111_setup_geometry(mt9m111, &rect, width, height, mt9m111->fmt->code);
	if (!ret) {
		mt9m111->rect = rect;
		mt9m111->width = width;
		mt9m111->height = height;
	}

	return ret;
}