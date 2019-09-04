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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_PAD_SINK ; 
 int /*<<< orphan*/  CCDC_PAD_SOURCE_OF ; 
 int /*<<< orphan*/  CCDC_PAD_SOURCE_VP ; 
 int EINVAL ; 
 struct v4l2_rect* __ccdc_get_crop (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __ccdc_get_format (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdc_try_crop (struct isp_ccdc_device*,struct v4l2_mbus_framefmt*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  ccdc_try_format (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct isp_ccdc_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ccdc_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	format = __ccdc_get_format(ccdc, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	ccdc_try_format(ccdc, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == CCDC_PAD_SINK) {
		/* Reset the crop rectangle. */
		crop = __ccdc_get_crop(ccdc, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->format.width;
		crop->height = fmt->format.height;

		ccdc_try_crop(ccdc, &fmt->format, crop);

		/* Update the source formats. */
		format = __ccdc_get_format(ccdc, cfg, CCDC_PAD_SOURCE_OF,
					   fmt->which);
		*format = fmt->format;
		ccdc_try_format(ccdc, cfg, CCDC_PAD_SOURCE_OF, format,
				fmt->which);

		format = __ccdc_get_format(ccdc, cfg, CCDC_PAD_SOURCE_VP,
					   fmt->which);
		*format = fmt->format;
		ccdc_try_format(ccdc, cfg, CCDC_PAD_SOURCE_VP, format,
				fmt->which);
	}

	return 0;
}