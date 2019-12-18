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
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {int pad; int target; int flags; int /*<<< orphan*/  which; struct v4l2_rect r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; } ;
struct csi_priv {scalar_t__ stream_count; int /*<<< orphan*/  lock; struct v4l2_rect compose; struct v4l2_rect crop; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int CSI_NUM_PADS ; 
 int CSI_SINK_PAD ; 
 int EBUSY ; 
 int EINVAL ; 
 int V4L2_SEL_FLAG_KEEP_CONFIG ; 
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_CROP 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_rect* __csi_get_compose (struct csi_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_rect* __csi_get_crop (struct csi_priv*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __csi_get_fmt (struct csi_priv*,struct v4l2_subdev_pad_config*,int,int /*<<< orphan*/ ) ; 
 int csi_get_upstream_endpoint (struct csi_priv*,struct v4l2_fwnode_endpoint*) ; 
 int csi_set_scale (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csi_try_crop (struct csi_priv*,struct v4l2_rect*,struct v4l2_subdev_pad_config*,struct v4l2_mbus_framefmt*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_set_selection(struct v4l2_subdev *sd,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_selection *sel)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fwnode_endpoint upstream_ep = { .bus_type = 0 };
	struct v4l2_mbus_framefmt *infmt;
	struct v4l2_rect *crop, *compose;
	int pad, ret;

	if (sel->pad != CSI_SINK_PAD)
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

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, sel->which);
	crop = __csi_get_crop(priv, cfg, sel->which);
	compose = __csi_get_compose(priv, cfg, sel->which);

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		/*
		 * Modifying the crop rectangle always changes the format on
		 * the source pads. If the KEEP_CONFIG flag is set, just return
		 * the current crop rectangle.
		 */
		if (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) {
			sel->r = priv->crop;
			if (sel->which == V4L2_SUBDEV_FORMAT_TRY)
				*crop = sel->r;
			goto out;
		}

		csi_try_crop(priv, &sel->r, cfg, infmt, &upstream_ep);

		*crop = sel->r;

		/* Reset scaling to 1:1 */
		compose->width = crop->width;
		compose->height = crop->height;
		break;
	case V4L2_SEL_TGT_COMPOSE:
		/*
		 * Modifying the compose rectangle always changes the format on
		 * the source pads. If the KEEP_CONFIG flag is set, just return
		 * the current compose rectangle.
		 */
		if (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) {
			sel->r = priv->compose;
			if (sel->which == V4L2_SUBDEV_FORMAT_TRY)
				*compose = sel->r;
			goto out;
		}

		sel->r.left = 0;
		sel->r.top = 0;
		ret = csi_set_scale(&sel->r.width, crop->width, sel->flags);
		if (ret)
			goto out;
		ret = csi_set_scale(&sel->r.height, crop->height, sel->flags);
		if (ret)
			goto out;

		*compose = sel->r;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	/* Reset source pads to sink compose rectangle */
	for (pad = CSI_SINK_PAD + 1; pad < CSI_NUM_PADS; pad++) {
		struct v4l2_mbus_framefmt *outfmt;

		outfmt = __csi_get_fmt(priv, cfg, pad, sel->which);
		outfmt->width = compose->width;
		outfmt->height = compose->height;
	}

out:
	mutex_unlock(&priv->lock);
	return ret;
}