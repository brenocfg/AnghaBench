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
struct v4l2_fract {int numerator; unsigned int denominator; } ;
struct v4l2_subdev_frame_interval {struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;
struct ov772x_priv {scalar_t__ power_count; unsigned int fps; int /*<<< orphan*/  lock; int /*<<< orphan*/  win; int /*<<< orphan*/  cfmt; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int ov772x_select_fps (struct ov772x_priv*,struct v4l2_fract*) ; 
 int ov772x_set_frame_rate (struct ov772x_priv*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov772x_priv* to_ov772x (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov772x_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *ival)
{
	struct ov772x_priv *priv = to_ov772x(sd);
	struct v4l2_fract *tpf = &ival->interval;
	unsigned int fps;
	int ret = 0;

	mutex_lock(&priv->lock);

	if (priv->streaming) {
		ret = -EBUSY;
		goto error;
	}

	fps = ov772x_select_fps(priv, tpf);

	/*
	 * If the device is not powered up by the host driver do
	 * not apply any changes to H/W at this time. Instead
	 * the frame rate will be restored right after power-up.
	 */
	if (priv->power_count > 0) {
		ret = ov772x_set_frame_rate(priv, fps, priv->cfmt, priv->win);
		if (ret)
			goto error;
	}

	tpf->numerator = 1;
	tpf->denominator = fps;
	priv->fps = fps;

error:
	mutex_unlock(&priv->lock);

	return ret;
}