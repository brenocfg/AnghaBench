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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int EINVAL ; 
 int param_set_int (char const*,struct kernel_param const*) ; 

__attribute__((used)) static int param_set_axis(const char *val, const struct kernel_param *kp)
{
	int ret = param_set_int(val, kp);
	if (!ret) {
		int val = *(int *)kp->arg;
		if (val < 0)
			val = -val;
		if (!val || val > 3)
			return -EINVAL;
	}
	return ret;
}