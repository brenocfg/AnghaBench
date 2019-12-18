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
struct v4l2_subdev_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; } ;
struct media_link {int dummy; } ;
struct imx7_csi {int is_csi2; int /*<<< orphan*/  lock; struct v4l2_fwnode_endpoint upstream_ep; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int imx7_csi_get_upstream_endpoint (struct imx7_csi*,struct v4l2_fwnode_endpoint*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int v4l2_subdev_link_validate_default (struct v4l2_subdev*,struct media_link*,struct v4l2_subdev_format*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int imx7_csi_pad_link_validate(struct v4l2_subdev *sd,
				      struct media_link *link,
				      struct v4l2_subdev_format *source_fmt,
				      struct v4l2_subdev_format *sink_fmt)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	struct v4l2_fwnode_endpoint upstream_ep = {};
	int ret;

	ret = v4l2_subdev_link_validate_default(sd, link, source_fmt, sink_fmt);
	if (ret)
		return ret;

	ret = imx7_csi_get_upstream_endpoint(csi, &upstream_ep, true);
	if (ret) {
		v4l2_err(&csi->sd, "failed to find upstream endpoint\n");
		return ret;
	}

	mutex_lock(&csi->lock);

	csi->upstream_ep = upstream_ep;
	csi->is_csi2 = (upstream_ep.bus_type == V4L2_MBUS_CSI2_DPHY);

	mutex_unlock(&csi->lock);

	return 0;
}