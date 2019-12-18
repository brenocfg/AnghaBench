#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct vpfe_subdev_info {int /*<<< orphan*/  grp_id; } ;
struct TYPE_12__ {int active_pixels; int active_lines; int /*<<< orphan*/  frame_format; } ;
struct TYPE_11__ {int width; int height; scalar_t__ left; scalar_t__ top; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_9__ {struct v4l2_pix_format pix; } ;
struct TYPE_10__ {TYPE_1__ fmt; } ;
struct vpfe_device {int std_index; int /*<<< orphan*/  v4l2_dev; TYPE_4__ std_info; TYPE_3__ crop; TYPE_2__ fmt; struct vpfe_subdev_info* current_subdev; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct TYPE_13__ {int (* get_line_length ) () ;} ;
struct TYPE_15__ {TYPE_5__ hw_ops; } ;
struct TYPE_14__ {int std_id; int width; int height; int /*<<< orphan*/  frame_format; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV10_2X10 ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 TYPE_7__* ccdc_dev ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  pad ; 
 int stub1 () ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,struct v4l2_mbus_framefmt*) ; 
 int vpfe_config_ccdc_image_format (struct vpfe_device*) ; 
 TYPE_6__* vpfe_standards ; 

__attribute__((used)) static int vpfe_config_image_format(struct vpfe_device *vpfe_dev,
				    v4l2_std_id std_id)
{
	struct vpfe_subdev_info *sdinfo = vpfe_dev->current_subdev;
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	struct v4l2_mbus_framefmt *mbus_fmt = &fmt.format;
	struct v4l2_pix_format *pix = &vpfe_dev->fmt.fmt.pix;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(vpfe_standards); i++) {
		if (vpfe_standards[i].std_id & std_id) {
			vpfe_dev->std_info.active_pixels =
					vpfe_standards[i].width;
			vpfe_dev->std_info.active_lines =
					vpfe_standards[i].height;
			vpfe_dev->std_info.frame_format =
					vpfe_standards[i].frame_format;
			vpfe_dev->std_index = i;
			break;
		}
	}

	if (i ==  ARRAY_SIZE(vpfe_standards)) {
		v4l2_err(&vpfe_dev->v4l2_dev, "standard not supported\n");
		return -EINVAL;
	}

	vpfe_dev->crop.top = 0;
	vpfe_dev->crop.left = 0;
	vpfe_dev->crop.width = vpfe_dev->std_info.active_pixels;
	vpfe_dev->crop.height = vpfe_dev->std_info.active_lines;
	pix->width = vpfe_dev->crop.width;
	pix->height = vpfe_dev->crop.height;

	/* first field and frame format based on standard frame format */
	if (vpfe_dev->std_info.frame_format) {
		pix->field = V4L2_FIELD_INTERLACED;
		/* assume V4L2_PIX_FMT_UYVY as default */
		pix->pixelformat = V4L2_PIX_FMT_UYVY;
		v4l2_fill_mbus_format(mbus_fmt, pix,
				MEDIA_BUS_FMT_YUYV10_2X10);
	} else {
		pix->field = V4L2_FIELD_NONE;
		/* assume V4L2_PIX_FMT_SBGGR8 */
		pix->pixelformat = V4L2_PIX_FMT_SBGGR8;
		v4l2_fill_mbus_format(mbus_fmt, pix,
				MEDIA_BUS_FMT_SBGGR8_1X8);
	}

	/* if sub device supports get_fmt, override the defaults */
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
			sdinfo->grp_id, pad, get_fmt, NULL, &fmt);

	if (ret && ret != -ENOIOCTLCMD) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"error in getting get_fmt from sub device\n");
		return ret;
	}
	v4l2_fill_pix_format(pix, mbus_fmt);
	pix->bytesperline = pix->width * 2;
	pix->sizeimage = pix->bytesperline * pix->height;

	/* Sets the values in CCDC */
	ret = vpfe_config_ccdc_image_format(vpfe_dev);
	if (ret)
		return ret;

	/* Update the values of sizeimage and bytesperline */
	pix->bytesperline = ccdc_dev->hw_ops.get_line_length();
	pix->sizeimage = pix->bytesperline * pix->height;

	return 0;
}