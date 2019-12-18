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
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct isp_csi2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_PAD_SINK ; 
 int /*<<< orphan*/  CSI2_PAD_SOURCE ; 
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __csi2_get_format (struct isp_csi2_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csi2_try_format (struct isp_csi2_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct isp_csi2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __csi2_get_format(csi2, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	csi2_try_format(csi2, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == CSI2_PAD_SINK) {
		format = __csi2_get_format(csi2, cfg, CSI2_PAD_SOURCE,
					   fmt->which);
		*format = fmt->format;
		csi2_try_format(csi2, cfg, CSI2_PAD_SOURCE, format, fmt->which);
	}

	return 0;
}