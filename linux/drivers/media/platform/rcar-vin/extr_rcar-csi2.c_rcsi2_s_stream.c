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
struct v4l2_subdev {int dummy; } ;
struct rcar_csi2 {int stream_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  remote; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rcsi2_start (struct rcar_csi2*) ; 
 int /*<<< orphan*/  rcsi2_stop (struct rcar_csi2*) ; 
 struct rcar_csi2* sd_to_csi2 (struct v4l2_subdev*) ; 

__attribute__((used)) static int rcsi2_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct rcar_csi2 *priv = sd_to_csi2(sd);
	int ret = 0;

	mutex_lock(&priv->lock);

	if (!priv->remote) {
		ret = -ENODEV;
		goto out;
	}

	if (enable && priv->stream_count == 0) {
		ret = rcsi2_start(priv);
		if (ret)
			goto out;
	} else if (!enable && priv->stream_count == 1) {
		rcsi2_stop(priv);
	}

	priv->stream_count += enable ? 1 : -1;
out:
	mutex_unlock(&priv->lock);

	return ret;
}