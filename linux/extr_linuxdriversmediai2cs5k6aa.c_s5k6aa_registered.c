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
struct s5k6aa {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __s5k6aa_power_off (struct s5k6aa*) ; 
 int __s5k6aa_power_on (struct s5k6aa*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k6aa_check_fw_revision (struct s5k6aa*) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k6aa_registered(struct v4l2_subdev *sd)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	int ret;

	mutex_lock(&s5k6aa->lock);
	ret = __s5k6aa_power_on(s5k6aa);
	if (!ret) {
		msleep(100);
		ret = s5k6aa_check_fw_revision(s5k6aa);
		__s5k6aa_power_off(s5k6aa);
	}
	mutex_unlock(&s5k6aa->lock);

	return ret;
}