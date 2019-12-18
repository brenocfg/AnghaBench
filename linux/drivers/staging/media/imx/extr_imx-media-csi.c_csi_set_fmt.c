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
struct v4l2_subdev_format {int pad; int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int dummy; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; } ;
struct imx_media_pixfmt {int dummy; } ;
struct csi_priv {scalar_t__ stream_count; int /*<<< orphan*/  lock; struct imx_media_pixfmt const** cc; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int CSI_NUM_PADS ; 
 int CSI_SINK_PAD ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_rect* __csi_get_compose (struct csi_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_rect* __csi_get_crop (struct csi_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __csi_get_fmt (struct csi_priv*,struct v4l2_subdev_pad_config*,int,int /*<<< orphan*/ ) ; 
 int csi_get_upstream_endpoint (struct csi_priv*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  csi_try_fmt (struct csi_priv*,struct v4l2_fwnode_endpoint*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*,struct v4l2_rect*,struct v4l2_rect*,struct imx_media_pixfmt const**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_set_fmt(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_format *sdformat)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fwnode_endpoint upstream_ep = { .bus_type = 0 };
	const struct imx_media_pixfmt *cc;
	struct v4l2_mbus_framefmt *fmt;
	struct v4l2_rect *crop, *compose;
	int ret;

	if (sdformat->pad >= CSI_NUM_PADS)
		return -EINVAL;

	ret = csi_get_upstream_endpoint(priv, &upstream_ep);
	if (ret) {
		v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
		return ret;
	}

	mutex_lock(&priv->lock);

	if (priv->stream_count > 0) {
		ret = -EBUSY;
		goto out;
	}

	crop = __csi_get_crop(priv, cfg, sdformat->which);
	compose = __csi_get_compose(priv, cfg, sdformat->which);

	csi_try_fmt(priv, &upstream_ep, cfg, sdformat, crop, compose, &cc);

	fmt = __csi_get_fmt(priv, cfg, sdformat->pad, sdformat->which);
	*fmt = sdformat->format;

	if (sdformat->pad == CSI_SINK_PAD) {
		int pad;

		/* propagate format to source pads */
		for (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) {
			const struct imx_media_pixfmt *outcc;
			struct v4l2_mbus_framefmt *outfmt;
			struct v4l2_subdev_format format;

			format.pad = pad;
			format.which = sdformat->which;
			format.format = sdformat->format;
			csi_try_fmt(priv, &upstream_ep, cfg, &format,
				    NULL, compose, &outcc);

			outfmt = __csi_get_fmt(priv, cfg, pad, sdformat->which);
			*outfmt = format.format;

			if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
				priv->cc[pad] = outcc;
		}
	}

	if (sdformat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		priv->cc[sdformat->pad] = cc;

out:
	mutex_unlock(&priv->lock);
	return ret;
}