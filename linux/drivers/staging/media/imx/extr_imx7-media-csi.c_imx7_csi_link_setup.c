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
struct v4l2_subdev {int dummy; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {int /*<<< orphan*/  name; } ;
struct imx7_csi {int /*<<< orphan*/  lock; struct v4l2_subdev* src_sd; struct media_entity* sink; int /*<<< orphan*/  ctrl_hdlr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_deinit (struct imx7_csi*) ; 
 int imx7_csi_init (struct imx7_csi*) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx7_csi_link_setup(struct media_entity *entity,
			       const struct media_pad *local,
			       const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);
	struct v4l2_subdev *remote_sd;
	int ret = 0;

	dev_dbg(csi->dev, "link setup %s -> %s\n", remote->entity->name,
		local->entity->name);

	mutex_lock(&csi->lock);

	if (local->flags & MEDIA_PAD_FL_SINK) {
		if (!is_media_entity_v4l2_subdev(remote->entity)) {
			ret = -EINVAL;
			goto unlock;
		}

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (csi->src_sd) {
				ret = -EBUSY;
				goto unlock;
			}
			csi->src_sd = remote_sd;
		} else {
			csi->src_sd = NULL;
		}

		goto init;
	}

	/* source pad */
	if (flags & MEDIA_LNK_FL_ENABLED) {
		if (csi->sink) {
			ret = -EBUSY;
			goto unlock;
		}
		csi->sink = remote->entity;
	} else {
		v4l2_ctrl_handler_free(&csi->ctrl_hdlr);
		v4l2_ctrl_handler_init(&csi->ctrl_hdlr, 0);
		csi->sink = NULL;
	}

init:
	if (csi->sink || csi->src_sd)
		ret = imx7_csi_init(csi);
	else
		imx7_csi_deinit(csi);

unlock:
	mutex_unlock(&csi->lock);

	return ret;
}