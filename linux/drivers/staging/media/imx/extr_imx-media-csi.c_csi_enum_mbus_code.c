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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int pad; int /*<<< orphan*/  index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; } ;
struct imx_media_pixfmt {int /*<<< orphan*/  cs; } ;
struct csi_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
#define  CSI_SINK_PAD 130 
#define  CSI_SRC_PAD_DIRECT 129 
#define  CSI_SRC_PAD_IDMAC 128 
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  CS_SEL_RGB ; 
 int /*<<< orphan*/  CS_SEL_YUV ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPUV3_COLORSPACE_YUV ; 
 struct v4l2_mbus_framefmt* __csi_get_fmt (struct csi_priv*,struct v4l2_subdev_pad_config*,int,int /*<<< orphan*/ ) ; 
 int csi_get_upstream_endpoint (struct csi_priv*,struct v4l2_fwnode_endpoint*) ; 
 int imx_media_enum_ipu_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx_media_enum_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct imx_media_pixfmt* imx_media_find_mbus_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requires_passthrough (struct v4l2_fwnode_endpoint*,struct v4l2_mbus_framefmt*,struct imx_media_pixfmt const*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_enum_mbus_code(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_mbus_code_enum *code)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fwnode_endpoint upstream_ep = { .bus_type = 0 };
	const struct imx_media_pixfmt *incc;
	struct v4l2_mbus_framefmt *infmt;
	int ret = 0;

	mutex_lock(&priv->lock);

	infmt = __csi_get_fmt(priv, cfg, CSI_SINK_PAD, code->which);
	incc = imx_media_find_mbus_format(infmt->code, CS_SEL_ANY, true);

	switch (code->pad) {
	case CSI_SINK_PAD:
		ret = imx_media_enum_mbus_format(&code->code, code->index,
						 CS_SEL_ANY, true);
		break;
	case CSI_SRC_PAD_DIRECT:
	case CSI_SRC_PAD_IDMAC:
		ret = csi_get_upstream_endpoint(priv, &upstream_ep);
		if (ret) {
			v4l2_err(&priv->sd, "failed to find upstream endpoint\n");
			goto out;
		}

		if (requires_passthrough(&upstream_ep, infmt, incc)) {
			if (code->index != 0) {
				ret = -EINVAL;
				goto out;
			}
			code->code = infmt->code;
		} else {
			u32 cs_sel = (incc->cs == IPUV3_COLORSPACE_YUV) ?
				CS_SEL_YUV : CS_SEL_RGB;
			ret = imx_media_enum_ipu_format(&code->code,
							code->index,
							cs_sel);
		}
		break;
	default:
		ret = -EINVAL;
	}

out:
	mutex_unlock(&priv->lock);
	return ret;
}