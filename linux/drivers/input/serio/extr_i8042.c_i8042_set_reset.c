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
struct kernel_param {int* arg; } ;
typedef  enum i8042_controller_reset_mode { ____Placeholder_i8042_controller_reset_mode } i8042_controller_reset_mode ;

/* Variables and functions */
 int I8042_RESET_ALWAYS ; 
 int I8042_RESET_NEVER ; 
 int kstrtobool (char const*,int*) ; 

__attribute__((used)) static int i8042_set_reset(const char *val, const struct kernel_param *kp)
{
	enum i8042_controller_reset_mode *arg = kp->arg;
	int error;
	bool reset;

	if (val) {
		error = kstrtobool(val, &reset);
		if (error)
			return error;
	} else {
		reset = true;
	}

	*arg = reset ? I8042_RESET_ALWAYS : I8042_RESET_NEVER;
	return 0;
}