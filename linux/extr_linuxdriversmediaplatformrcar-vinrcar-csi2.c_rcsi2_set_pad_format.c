#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct rcar_csi2 {struct v4l2_mbus_framefmt mf; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 TYPE_1__* rcar_csi2_formats ; 
 int /*<<< orphan*/  rcsi2_code_to_fmt (int /*<<< orphan*/ ) ; 
 struct rcar_csi2* sd_to_csi2 (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcsi2_set_pad_format(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_format *format)
{
	struct rcar_csi2 *priv = sd_to_csi2(sd);
	struct v4l2_mbus_framefmt *framefmt;

	if (!rcsi2_code_to_fmt(format->format.code))
		format->format.code = rcar_csi2_formats[0].code;

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		priv->mf = format->format;
	} else {
		framefmt = v4l2_subdev_get_try_format(sd, cfg, 0);
		*framefmt = format->format;
	}

	return 0;
}