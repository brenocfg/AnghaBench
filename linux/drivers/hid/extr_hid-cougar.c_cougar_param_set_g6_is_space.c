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
 int /*<<< orphan*/  cougar_fix_g6_mapping () ; 
 int param_set_bool (char const*,struct kernel_param const*) ; 

__attribute__((used)) static int cougar_param_set_g6_is_space(const char *val,
					const struct kernel_param *kp)
{
	int ret;

	ret = param_set_bool(val, kp);
	if (ret)
		return ret;

	cougar_fix_g6_mapping();

	return 0;
}