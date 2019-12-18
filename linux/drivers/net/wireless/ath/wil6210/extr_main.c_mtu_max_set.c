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
 int EINVAL ; 
 int WIL_MAX_ETH_MTU ; 
 int mtu_max ; 
 int param_set_uint (char const*,struct kernel_param const*) ; 

__attribute__((used)) static int mtu_max_set(const char *val, const struct kernel_param *kp)
{
	int ret;

	/* sets mtu_max directly. no need to restore it in case of
	 * illegal value since we assume this will fail insmod
	 */
	ret = param_set_uint(val, kp);
	if (ret)
		return ret;

	if (mtu_max < 68 || mtu_max > WIL_MAX_ETH_MTU)
		ret = -EINVAL;

	return ret;
}