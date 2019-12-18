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
struct v4l2_subdev_format {scalar_t__ which; size_t pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct csi2tx_priv {struct v4l2_mbus_framefmt* pad_fmts; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t) ; 
 struct csi2tx_priv* v4l2_subdev_to_csi2tx (struct v4l2_subdev*) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
__csi2tx_get_pad_format(struct v4l2_subdev *subdev,
			struct v4l2_subdev_pad_config *cfg,
			struct v4l2_subdev_format *fmt)
{
	struct csi2tx_priv *csi2tx = v4l2_subdev_to_csi2tx(subdev);

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_format(subdev, cfg,
						  fmt->pad);

	return &csi2tx->pad_fmts[fmt->pad];
}