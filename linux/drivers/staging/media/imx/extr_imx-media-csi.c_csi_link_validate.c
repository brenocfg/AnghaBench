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
struct v4l2_subdev_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; } ;
struct media_link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct csi_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  csi_id; int /*<<< orphan*/  ipu; int /*<<< orphan*/ * format_mbus; int /*<<< orphan*/  csi; TYPE_1__ sd; struct v4l2_fwnode_endpoint upstream_ep; } ;

/* Variables and functions */
 size_t CSI_SINK_PAD ; 
 int csi_get_upstream_endpoint (struct csi_priv*,struct v4l2_fwnode_endpoint*) ; 
 int imx_media_find_mipi_csi2_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_csi_set_mipi_datatype (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_set_csi_src_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_parallel_bus (struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int v4l2_subdev_link_validate_default (struct v4l2_subdev*,struct media_link*,struct v4l2_subdev_format*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int csi_link_validate(struct v4l2_subdev *sd,
			     struct media_link *link,
			     struct v4l2_subdev_format *source_fmt,
			     struct v4l2_subdev_format *sink_fmt)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fwnode_endpoint upstream_ep = { .bus_type = 0 };
	bool is_csi2;
	int ret;

	ret = v4l2_subdev_link_validate_default(sd, link,
						source_fmt, sink_fmt);
	if (ret)
		return ret;

	ret = csi_get_upstream_endpoint(priv, &upstream_ep);
	if (ret) {
		v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
		return ret;
	}

	mutex_lock(&priv->lock);

	priv->upstream_ep = upstream_ep;
	is_csi2 = !is_parallel_bus(&upstream_ep);
	if (is_csi2) {
		int vc_num = 0;
		/*
		 * NOTE! It seems the virtual channels from the mipi csi-2
		 * receiver are used only for routing by the video mux's,
		 * or for hard-wired routing to the CSI's. Once the stream
		 * enters the CSI's however, they are treated internally
		 * in the IPU as virtual channel 0.
		 */
#if 0
		mutex_unlock(&priv->lock);
		vc_num = imx_media_find_mipi_csi2_channel(&priv->sd.entity);
		if (vc_num < 0)
			return vc_num;
		mutex_lock(&priv->lock);
#endif
		ipu_csi_set_mipi_datatype(priv->csi, vc_num,
					  &priv->format_mbus[CSI_SINK_PAD]);
	}

	/* select either parallel or MIPI-CSI2 as input to CSI */
	ipu_set_csi_src_mux(priv->ipu, priv->csi_id, is_csi2);

	mutex_unlock(&priv->lock);
	return ret;
}