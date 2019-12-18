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
struct s5k5baf {int streaming; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k5baf_clear_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_config (struct s5k5baf*) ; 
 int s5k5baf_hw_set_crop_rects (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_stream (struct s5k5baf*,int) ; 
 int /*<<< orphan*/  s5k5baf_i2c_write (struct s5k5baf*,int,int) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k5baf_s_stream(struct v4l2_subdev *sd, int on)
{
	struct s5k5baf *state = to_s5k5baf(sd);
	int ret;

	mutex_lock(&state->lock);

	if (state->streaming == !!on) {
		ret = 0;
		goto out;
	}

	if (on) {
		s5k5baf_hw_set_config(state);
		ret = s5k5baf_hw_set_crop_rects(state);
		if (ret < 0)
			goto out;
		s5k5baf_hw_set_stream(state, 1);
		s5k5baf_i2c_write(state, 0xb0cc, 0x000b);
	} else {
		s5k5baf_hw_set_stream(state, 0);
	}
	ret = s5k5baf_clear_error(state);
	if (!ret)
		state->streaming = !state->streaming;

out:
	mutex_unlock(&state->lock);

	return ret;
}