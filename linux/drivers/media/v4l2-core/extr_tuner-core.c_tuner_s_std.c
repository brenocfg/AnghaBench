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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct tuner {int /*<<< orphan*/  std; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freq (struct tuner*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_mode (struct tuner*,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tuner_fixup_std (struct tuner*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tuner_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct tuner *t = to_tuner(sd);

	if (set_mode(t, V4L2_TUNER_ANALOG_TV))
		return 0;

	t->std = tuner_fixup_std(t, std);
	if (t->std != std)
		dprintk("Fixup standard %llx to %llx\n", std, t->std);
	set_freq(t, 0);
	return 0;
}