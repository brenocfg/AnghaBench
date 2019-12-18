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
typedef  int u32 ;
struct v4l2_subdev {int grp_id; } ;
struct media_pad {int flags; scalar_t__ index; struct media_entity* entity; } ;
struct media_entity {int /*<<< orphan*/  name; } ;
struct csi_priv {scalar_t__ active_output_pad; int /*<<< orphan*/  lock; struct media_entity* sink; int /*<<< orphan*/  dest; scalar_t__ fim; int /*<<< orphan*/  ctrl_hdlr; struct v4l2_subdev* src_sd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CSI_SRC_PAD_IDMAC ; 
 int EBUSY ; 
 int EINVAL ; 
#define  IMX_MEDIA_GRP_ID_IPU_IC_PRP 129 
#define  IMX_MEDIA_GRP_ID_IPU_VDIC 128 
 int /*<<< orphan*/  IPU_CSI_DEST_IC ; 
 int /*<<< orphan*/  IPU_CSI_DEST_IDMAC ; 
 int /*<<< orphan*/  IPU_CSI_DEST_VDIC ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx_media_fim_add_controls (scalar_t__) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_video_device (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_link_setup(struct media_entity *entity,
			  const struct media_pad *local,
			  const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_subdev *remote_sd;
	int ret = 0;

	dev_dbg(priv->dev, "link setup %s -> %s\n", remote->entity->name,
		local->entity->name);

	mutex_lock(&priv->lock);

	if (local->flags & MEDIA_PAD_FL_SINK) {
		if (!is_media_entity_v4l2_subdev(remote->entity)) {
			ret = -EINVAL;
			goto out;
		}

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (priv->src_sd) {
				ret = -EBUSY;
				goto out;
			}
			priv->src_sd = remote_sd;
		} else {
			priv->src_sd = NULL;
		}

		goto out;
	}

	/* this is a source pad */

	if (flags & MEDIA_LNK_FL_ENABLED) {
		if (priv->sink) {
			ret = -EBUSY;
			goto out;
		}
	} else {
		v4l2_ctrl_handler_free(&priv->ctrl_hdlr);
		v4l2_ctrl_handler_init(&priv->ctrl_hdlr, 0);
		priv->sink = NULL;
		/* do not apply IC burst alignment in csi_try_crop */
		priv->active_output_pad = CSI_SRC_PAD_IDMAC;
		goto out;
	}

	/* record which output pad is now active */
	priv->active_output_pad = local->index;

	/* set CSI destination */
	if (local->index == CSI_SRC_PAD_IDMAC) {
		if (!is_media_entity_v4l2_video_device(remote->entity)) {
			ret = -EINVAL;
			goto out;
		}

		if (priv->fim) {
			ret = imx_media_fim_add_controls(priv->fim);
			if (ret)
				goto out;
		}

		priv->dest = IPU_CSI_DEST_IDMAC;
	} else {
		if (!is_media_entity_v4l2_subdev(remote->entity)) {
			ret = -EINVAL;
			goto out;
		}

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);
		switch (remote_sd->grp_id) {
		case IMX_MEDIA_GRP_ID_IPU_VDIC:
			priv->dest = IPU_CSI_DEST_VDIC;
			break;
		case IMX_MEDIA_GRP_ID_IPU_IC_PRP:
			priv->dest = IPU_CSI_DEST_IC;
			break;
		default:
			ret = -EINVAL;
			goto out;
		}
	}

	priv->sink = remote->entity;
out:
	mutex_unlock(&priv->lock);
	return ret;
}