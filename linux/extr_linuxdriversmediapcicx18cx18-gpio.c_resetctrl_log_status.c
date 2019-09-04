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
struct cx18 {int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_INFO_DEV (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resetctrl_log_status(struct v4l2_subdev *sd)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);

	mutex_lock(&cx->gpio_lock);
	CX18_INFO_DEV(sd, "GPIO:  direction 0x%08x, value 0x%08x\n",
		      cx->gpio_dir, cx->gpio_val);
	mutex_unlock(&cx->gpio_lock);
	return 0;
}