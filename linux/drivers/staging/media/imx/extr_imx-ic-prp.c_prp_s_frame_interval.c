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
struct TYPE_2__ {scalar_t__ numerator; scalar_t__ denominator; } ;
struct v4l2_subdev_frame_interval {scalar_t__ pad; TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;
struct prp_priv {int /*<<< orphan*/  lock; TYPE_1__ frame_interval; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PRP_NUM_PADS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct prp_priv* sd_to_priv (struct v4l2_subdev*) ; 

__attribute__((used)) static int prp_s_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_frame_interval *fi)
{
	struct prp_priv *priv = sd_to_priv(sd);

	if (fi->pad >= PRP_NUM_PADS)
		return -EINVAL;

	mutex_lock(&priv->lock);

	/* No limits on valid frame intervals */
	if (fi->interval.numerator == 0 || fi->interval.denominator == 0)
		fi->interval = priv->frame_interval;
	else
		priv->frame_interval = fi->interval;

	mutex_unlock(&priv->lock);

	return 0;
}