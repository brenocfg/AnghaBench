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
struct v4l2_subdev_mbus_code_enum {int pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  CCDC_PAD_SINK 130 
#define  CCDC_PAD_SOURCE_OF 129 
#define  CCDC_PAD_SOURCE_VP 128 
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_1X16 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_1X16 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_2X8 ; 
 struct v4l2_mbus_framefmt* __ccdc_get_format (struct isp_ccdc_device*,struct v4l2_subdev_pad_config*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ccdc_fmts ; 
 struct isp_ccdc_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ccdc_enum_mbus_code(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code)
{
	struct isp_ccdc_device *ccdc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	switch (code->pad) {
	case CCDC_PAD_SINK:
		if (code->index >= ARRAY_SIZE(ccdc_fmts))
			return -EINVAL;

		code->code = ccdc_fmts[code->index];
		break;

	case CCDC_PAD_SOURCE_OF:
		format = __ccdc_get_format(ccdc, cfg, code->pad,
					   code->which);

		if (format->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    format->code == MEDIA_BUS_FMT_UYVY8_2X8) {
			/* In YUV mode the CCDC can swap bytes. */
			if (code->index == 0)
				code->code = MEDIA_BUS_FMT_YUYV8_1X16;
			else if (code->index == 1)
				code->code = MEDIA_BUS_FMT_UYVY8_1X16;
			else
				return -EINVAL;
		} else {
			/* In raw mode, no configurable format confversion is
			 * available.
			 */
			if (code->index == 0)
				code->code = format->code;
			else
				return -EINVAL;
		}
		break;

	case CCDC_PAD_SOURCE_VP:
		/* The CCDC supports no configurable format conversion
		 * compatible with the video port. Enumerate a single output
		 * format code.
		 */
		if (code->index != 0)
			return -EINVAL;

		format = __ccdc_get_format(ccdc, cfg, code->pad,
					   code->which);

		/* A pixel code equal to 0 means that the video port doesn't
		 * support the input format. Don't enumerate any pixel code.
		 */
		if (format->code == 0)
			return -EINVAL;

		code->code = format->code;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}