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
struct v4l2_subdev_frame_interval {size_t pad; int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct csi_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/ * frame_interval; } ;

/* Variables and functions */
 size_t CSI_NUM_PADS ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_g_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_frame_interval *fi)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);

	if (fi->pad >= CSI_NUM_PADS)
		return -EINVAL;

	mutex_lock(&priv->lock);

	fi->interval = priv->frame_interval[fi->pad];

	mutex_unlock(&priv->lock);

	return 0;
}