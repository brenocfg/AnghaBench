#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ left; scalar_t__ top; } ;
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {struct v4l2_pix_format pix; } ;
struct TYPE_11__ {TYPE_1__ fmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  frame_format; int /*<<< orphan*/  active_lines; int /*<<< orphan*/  active_pixels; } ;
struct vpfe_device {int std_index; TYPE_3__ crop; int /*<<< orphan*/  bpp; TYPE_5__ fmt; TYPE_2__ std_info; } ;
struct TYPE_10__ {int std_id; int /*<<< orphan*/  frame_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int __vpfe_get_format (struct vpfe_device*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int vpfe_config_ccdc_image_format (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_err (struct vpfe_device*,char*) ; 
 TYPE_4__* vpfe_standards ; 

__attribute__((used)) static int vpfe_config_image_format(struct vpfe_device *vpfe,
				    v4l2_std_id std_id)
{
	struct v4l2_pix_format *pix = &vpfe->fmt.fmt.pix;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(vpfe_standards); i++) {
		if (vpfe_standards[i].std_id & std_id) {
			vpfe->std_info.active_pixels =
					vpfe_standards[i].width;
			vpfe->std_info.active_lines =
					vpfe_standards[i].height;
			vpfe->std_info.frame_format =
					vpfe_standards[i].frame_format;
			vpfe->std_index = i;

			break;
		}
	}

	if (i ==  ARRAY_SIZE(vpfe_standards)) {
		vpfe_err(vpfe, "standard not supported\n");
		return -EINVAL;
	}

	vpfe->crop.top = vpfe->crop.left = 0;
	vpfe->crop.width = vpfe->std_info.active_pixels;
	vpfe->crop.height = vpfe->std_info.active_lines;
	pix->width = vpfe->crop.width;
	pix->height = vpfe->crop.height;
	pix->pixelformat = V4L2_PIX_FMT_YUYV;

	/* first field and frame format based on standard frame format */
	if (vpfe->std_info.frame_format)
		pix->field = V4L2_FIELD_INTERLACED;
	else
		pix->field = V4L2_FIELD_NONE;

	ret = __vpfe_get_format(vpfe, &vpfe->fmt, &vpfe->bpp);
	if (ret)
		return ret;

	/* Update the crop window based on found values */
	vpfe->crop.width = pix->width;
	vpfe->crop.height = pix->height;

	return vpfe_config_ccdc_image_format(vpfe);
}