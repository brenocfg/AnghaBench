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
struct csid_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSM_CSID_PAD_SINK ; 
 int /*<<< orphan*/  MSM_CSID_PAD_SRC ; 
 struct v4l2_mbus_framefmt* __csid_get_format (struct csid_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csid_try_format (struct csid_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct csid_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csid_set_format(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct csid_device *csid = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __csid_get_format(csid, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	csid_try_format(csid, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == MSM_CSID_PAD_SINK) {
		format = __csid_get_format(csid, cfg, MSM_CSID_PAD_SRC,
					   fmt->which);

		*format = fmt->format;
		csid_try_format(csid, cfg, MSM_CSID_PAD_SRC, format,
				fmt->which);
	}

	return 0;
}