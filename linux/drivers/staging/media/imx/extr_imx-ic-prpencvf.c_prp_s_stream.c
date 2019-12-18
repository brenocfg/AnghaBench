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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct prp_priv {int stream_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  sink; int /*<<< orphan*/  src_sd; } ;
struct imx_ic_priv {int /*<<< orphan*/  ipu_dev; struct prp_priv* task_priv; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int prp_start (struct prp_priv*) ; 
 int /*<<< orphan*/  prp_stop (struct prp_priv*) ; 
 struct imx_ic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int prp_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);
	struct prp_priv *priv = ic_priv->task_priv;
	int ret = 0;

	mutex_lock(&priv->lock);

	if (!priv->src_sd || !priv->sink) {
		ret = -EPIPE;
		goto out;
	}

	/*
	 * enable/disable streaming only if stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	if (priv->stream_count != !enable)
		goto update_count;

	dev_dbg(ic_priv->ipu_dev, "%s: stream %s\n", sd->name,
		enable ? "ON" : "OFF");

	if (enable)
		ret = prp_start(priv);
	else
		prp_stop(priv);
	if (ret)
		goto out;

update_count:
	priv->stream_count += enable ? 1 : -1;
	if (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	return ret;
}