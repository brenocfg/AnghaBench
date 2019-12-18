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
struct v4l2_fract {int dummy; } ;
struct csi_priv {size_t active_output_pad; scalar_t__ dest; int /*<<< orphan*/  src_sd; scalar_t__ fim; int /*<<< orphan*/  sd; int /*<<< orphan*/  csi; struct v4l2_fract* frame_interval; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 scalar_t__ IPU_CSI_DEST_IDMAC ; 
 int csi_idmac_start (struct csi_priv*) ; 
 int /*<<< orphan*/  csi_idmac_stop (struct csi_priv*) ; 
 int csi_setup (struct csi_priv*) ; 
 int imx_media_fim_set_stream (scalar_t__,struct v4l2_fract*,int) ; 
 int ipu_csi_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int csi_start(struct csi_priv *priv)
{
	struct v4l2_fract *output_fi;
	int ret;

	output_fi = &priv->frame_interval[priv->active_output_pad];

	/* start upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 1);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	if (ret)
		return ret;

	if (priv->dest == IPU_CSI_DEST_IDMAC) {
		ret = csi_idmac_start(priv);
		if (ret)
			goto stop_upstream;
	}

	ret = csi_setup(priv);
	if (ret)
		goto idmac_stop;

	/* start the frame interval monitor */
	if (priv->fim && priv->dest == IPU_CSI_DEST_IDMAC) {
		ret = imx_media_fim_set_stream(priv->fim, output_fi, true);
		if (ret)
			goto idmac_stop;
	}

	ret = ipu_csi_enable(priv->csi);
	if (ret) {
		v4l2_err(&priv->sd, "CSI enable error: %d\n", ret);
		goto fim_off;
	}

	return 0;

fim_off:
	if (priv->fim && priv->dest == IPU_CSI_DEST_IDMAC)
		imx_media_fim_set_stream(priv->fim, NULL, false);
idmac_stop:
	if (priv->dest == IPU_CSI_DEST_IDMAC)
		csi_idmac_stop(priv);
stop_upstream:
	v4l2_subdev_call(priv->src_sd, video, s_stream, 0);
	return ret;
}