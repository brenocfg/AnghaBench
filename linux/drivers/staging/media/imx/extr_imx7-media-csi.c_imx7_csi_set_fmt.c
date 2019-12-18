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
struct v4l2_subdev_format {size_t pad; int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct imx_media_pixfmt {int dummy; } ;
struct imx7_csi {int /*<<< orphan*/  lock; struct imx_media_pixfmt const** cc; scalar_t__ is_streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t IMX7_CSI_PADS_NUM ; 
 size_t IMX7_CSI_PAD_SINK ; 
 size_t IMX7_CSI_PAD_SRC ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_mbus_framefmt* imx7_csi_get_format (struct imx7_csi*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int imx7_csi_try_fmt (struct imx7_csi*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*,struct imx_media_pixfmt const**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx7_csi_set_fmt(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *sdformat)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	const struct imx_media_pixfmt *outcc;
	struct v4l2_mbus_framefmt *outfmt;
	const struct imx_media_pixfmt *cc;
	struct v4l2_mbus_framefmt *fmt;
	struct v4l2_subdev_format format;
	int ret = 0;

	if (sdformat->pad >= IMX7_CSI_PADS_NUM)
		return -EINVAL;

	mutex_lock(&csi->lock);

	if (csi->is_streaming) {
		ret = -EBUSY;
		goto out_unlock;
	}

	ret = imx7_csi_try_fmt(csi, cfg, sdformat, &cc);
	if (ret < 0)
		goto out_unlock;

	fmt = imx7_csi_get_format(csi, cfg, sdformat->pad, sdformat->which);
	if (!fmt) {
		ret = -EINVAL;
		goto out_unlock;
	}

	*fmt = sdformat->format;

	if (sdformat->pad == IMX7_CSI_PAD_SINK) {
		/* propagate format to source pads */
		format.pad = IMX7_CSI_PAD_SRC;
		format.which = sdformat->which;
		format.format = sdformat->format;
		if (imx7_csi_try_fmt(csi, cfg, &format, &outcc)) {
			ret = -EINVAL;
			goto out_unlock;
		}
		outfmt = imx7_csi_get_format(csi, cfg, IMX7_CSI_PAD_SRC,
					     sdformat->which);
		*outfmt = format.format;

		if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			csi->cc[IMX7_CSI_PAD_SRC] = outcc;
	}

	if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		csi->cc[sdformat->pad] = cc;

out_unlock:
	mutex_unlock(&csi->lock);

	return ret;
}