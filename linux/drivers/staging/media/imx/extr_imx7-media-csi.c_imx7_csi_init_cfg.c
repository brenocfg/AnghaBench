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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct imx7_csi {int /*<<< orphan*/ * cc; } ;

/* Variables and functions */
 int IMX7_CSI_PADS_NUM ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int imx_media_init_mbus_fmt (struct v4l2_mbus_framefmt*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int) ; 

__attribute__((used)) static int imx7_csi_init_cfg(struct v4l2_subdev *sd,
			     struct v4l2_subdev_pad_config *cfg)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *mf;
	int ret;
	int i;

	for (i = 0; i < IMX7_CSI_PADS_NUM; i++) {
		mf = v4l2_subdev_get_try_format(sd, cfg, i);

		ret = imx_media_init_mbus_fmt(mf, 800, 600, 0, V4L2_FIELD_NONE,
					      &csi->cc[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}