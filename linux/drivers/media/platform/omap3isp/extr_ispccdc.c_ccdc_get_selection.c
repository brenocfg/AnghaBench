#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ pad; int target; int /*<<< orphan*/  which; TYPE_1__ r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_PAD_SINK ; 
 scalar_t__ CCDC_PAD_SOURCE_OF ; 
 int EINVAL ; 
 void* INT_MAX ; 
#define  V4L2_SEL_TGT_CROP 129 
#define  V4L2_SEL_TGT_CROP_BOUNDS 128 
 TYPE_1__* __ccdc_get_crop (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __ccdc_get_format (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdc_try_crop (struct isp_ccdc_device*,struct v4l2_mbus_framefmt*,TYPE_1__*) ; 
 struct isp_ccdc_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ccdc_get_selection(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_selection *sel)
{
	struct isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (sel->pad != CCDC_PAD_SOURCE_OF)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = INT_MAX;
		sel->r.height = INT_MAX;

		format = __ccdc_get_format(ccdc, cfg, CCDC_PAD_SINK, sel->which);
		ccdc_try_crop(ccdc, format, &sel->r);
		break;

	case V4L2_SEL_TGT_CROP:
		sel->r = *__ccdc_get_crop(ccdc, cfg, sel->which);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}