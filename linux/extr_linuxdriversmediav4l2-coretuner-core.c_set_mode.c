#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct analog_demod_ops {int /*<<< orphan*/  (* standby ) (TYPE_2__*) ;} ;
struct TYPE_3__ {struct analog_demod_ops analog_ops; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct tuner {int mode; int standby; TYPE_2__ fe; } ;
typedef  enum v4l2_tuner_type { ____Placeholder_v4l2_tuner_type } v4l2_tuner_type ;

/* Variables and functions */
 int EINVAL ; 
 int check_mode (struct tuner*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int set_mode(struct tuner *t, enum v4l2_tuner_type mode)
{
	struct analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	if (mode != t->mode) {
		if (check_mode(t, mode) == -EINVAL) {
			dprintk("Tuner doesn't support mode %d. Putting tuner to sleep\n",
				  mode);
			t->standby = true;
			if (analog_ops->standby)
				analog_ops->standby(&t->fe);
			return -EINVAL;
		}
		t->mode = mode;
		dprintk("Changing to mode %d\n", mode);
	}
	return 0;
}