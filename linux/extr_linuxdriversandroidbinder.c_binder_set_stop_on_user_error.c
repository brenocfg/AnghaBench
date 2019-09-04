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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int binder_stop_on_user_error ; 
 int /*<<< orphan*/  binder_user_error_wait ; 
 int param_set_int (char const*,struct kernel_param const*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binder_set_stop_on_user_error(const char *val,
					 const struct kernel_param *kp)
{
	int ret;

	ret = param_set_int(val, kp);
	if (binder_stop_on_user_error < 2)
		wake_up(&binder_user_error_wait);
	return ret;
}