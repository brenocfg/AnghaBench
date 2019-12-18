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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct csis_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __s5pcsis_get_format (struct csis_state*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csis_state* sd_to_csis_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5pcsis_get_fmt(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct csis_state *state = sd_to_csis_state(sd);
	struct v4l2_mbus_framefmt *mf;

	mf = __s5pcsis_get_format(state, cfg, fmt->which);
	if (!mf)
		return -EINVAL;

	mutex_lock(&state->lock);
	fmt->format = *mf;
	mutex_unlock(&state->lock);
	return 0;
}