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
struct vdic_priv {int stream_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  ipu_dev; int /*<<< orphan*/  src; scalar_t__ csi_direct; int /*<<< orphan*/  sink_sd; } ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int EPIPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 struct vdic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vdic_start (struct vdic_priv*) ; 
 int /*<<< orphan*/  vdic_stop (struct vdic_priv*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int vdic_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct vdic_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_subdev *src_sd = NULL;
	int ret = 0;

	mutex_lock(&priv->lock);

	if (!priv->src || !priv->sink_sd) {
		ret = -EPIPE;
		goto out;
	}

	if (priv->csi_direct)
		src_sd = media_entity_to_v4l2_subdev(priv->src);

	/*
	 * enable/disable streaming only if stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	if (priv->stream_count != !enable)
		goto update_count;

	dev_dbg(priv->ipu_dev, "%s: stream %s\n", sd->name,
		enable ? "ON" : "OFF");

	if (enable)
		ret = vdic_start(priv);
	else
		vdic_stop(priv);
	if (ret)
		goto out;

	if (src_sd) {
		/* start/stop upstream */
		ret = v4l2_subdev_call(src_sd, video, s_stream, enable);
		ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
		if (ret) {
			if (enable)
				vdic_stop(priv);
			goto out;
		}
	}

update_count:
	priv->stream_count += enable ? 1 : -1;
	if (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	return ret;
}