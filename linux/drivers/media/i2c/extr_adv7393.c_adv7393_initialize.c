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
struct adv7393_state {int /*<<< orphan*/  std; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * adv7393_init_reg_val ; 
 int adv7393_setoutput (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int adv7393_setstd (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int adv7393_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adv7393_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int adv7393_initialize(struct v4l2_subdev *sd)
{
	struct adv7393_state *state = to_state(sd);
	int err = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(adv7393_init_reg_val); i += 2) {

		err = adv7393_write(sd, adv7393_init_reg_val[i],
					adv7393_init_reg_val[i+1]);
		if (err) {
			v4l2_err(sd, "Error initializing\n");
			return err;
		}
	}

	/* Configure for default video standard */
	err = adv7393_setoutput(sd, state->output);
	if (err < 0) {
		v4l2_err(sd, "Error setting output during init\n");
		return -EINVAL;
	}

	err = adv7393_setstd(sd, state->std);
	if (err < 0) {
		v4l2_err(sd, "Error setting std during init\n");
		return -EINVAL;
	}

	return err;
}