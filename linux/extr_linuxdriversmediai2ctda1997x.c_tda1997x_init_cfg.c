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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct tda1997x_state {int /*<<< orphan*/ * mbus_codes; } ;

/* Variables and functions */
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda1997x_init_cfg(struct v4l2_subdev *sd,
			     struct v4l2_subdev_pad_config *cfg)
{
	struct tda1997x_state *state = to_state(sd);
	struct v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_format(sd, cfg, 0);
	mf->code = state->mbus_codes[0];

	return 0;
}