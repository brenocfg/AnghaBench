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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct tuner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_freq (struct tuner*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_mode (struct tuner*,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 

__attribute__((used)) static int tuner_s_frequency(struct v4l2_subdev *sd, const struct v4l2_frequency *f)
{
	struct tuner *t = to_tuner(sd);

	if (set_mode(t, f->type) == 0)
		set_freq(t, f->frequency);
	return 0;
}