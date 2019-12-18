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
struct vdic_priv {size_t active_input_pad; int /*<<< orphan*/  lock; struct v4l2_fract* frame_interval; int /*<<< orphan*/  csi_direct; } ;
struct v4l2_fract {int denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_subdev_frame_interval {int pad; struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VDIC_SINK_PAD_DIRECT 130 
#define  VDIC_SINK_PAD_IDMAC 129 
#define  VDIC_SRC_PAD_DIRECT 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vdic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int vdic_s_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_frame_interval *fi)
{
	struct vdic_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fract *input_fi, *output_fi;
	int ret = 0;

	mutex_lock(&priv->lock);

	input_fi = &priv->frame_interval[priv->active_input_pad];
	output_fi = &priv->frame_interval[VDIC_SRC_PAD_DIRECT];

	switch (fi->pad) {
	case VDIC_SINK_PAD_DIRECT:
	case VDIC_SINK_PAD_IDMAC:
		/* No limits on valid input frame intervals */
		if (fi->interval.numerator == 0 ||
		    fi->interval.denominator == 0)
			fi->interval = priv->frame_interval[fi->pad];
		/* Reset output interval */
		*output_fi = fi->interval;
		if (priv->csi_direct)
			output_fi->denominator *= 2;
		break;
	case VDIC_SRC_PAD_DIRECT:
		/*
		 * frame rate at output pad is double input
		 * rate when using direct CSI->VDIC pipeline.
		 *
		 * TODO: implement VDIC frame skipping
		 */
		fi->interval = *input_fi;
		if (priv->csi_direct)
			fi->interval.denominator *= 2;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	priv->frame_interval[fi->pad] = fi->interval;
out:
	mutex_unlock(&priv->lock);
	return ret;
}