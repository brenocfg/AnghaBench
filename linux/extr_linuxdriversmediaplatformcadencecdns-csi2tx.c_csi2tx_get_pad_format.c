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
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSI2TX_PAD_SOURCE ; 
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __csi2tx_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int csi2tx_get_pad_format(struct v4l2_subdev *subdev,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_format *fmt)
{
	const struct v4l2_mbus_framefmt *format;

	/* Multiplexed pad? */
	if (fmt->pad == CSI2TX_PAD_SOURCE)
		return -EINVAL;

	format = __csi2tx_get_pad_format(subdev, cfg, fmt);
	if (!format)
		return -EINVAL;

	fmt->format = *format;

	return 0;
}