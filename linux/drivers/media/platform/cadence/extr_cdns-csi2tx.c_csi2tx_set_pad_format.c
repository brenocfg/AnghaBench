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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSI2TX_PAD_SOURCE ; 
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __csi2tx_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  csi2tx_get_fmt_from_mbus (int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt fmt_default ; 

__attribute__((used)) static int csi2tx_set_pad_format(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_format *fmt)
{
	const struct v4l2_mbus_framefmt *src_format = &fmt->format;
	struct v4l2_mbus_framefmt *dst_format;

	/* Multiplexed pad? */
	if (fmt->pad == CSI2TX_PAD_SOURCE)
		return -EINVAL;

	if (!csi2tx_get_fmt_from_mbus(fmt->format.code))
		src_format = &fmt_default;

	dst_format = __csi2tx_get_pad_format(subdev, cfg, fmt);
	if (!dst_format)
		return -EINVAL;

	*dst_format = *src_format;

	return 0;
}