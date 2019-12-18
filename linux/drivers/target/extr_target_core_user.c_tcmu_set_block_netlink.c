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
typedef  int u8 ;
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int tcmu_netlink_blocked ; 

__attribute__((used)) static int tcmu_set_block_netlink(const char *str,
				  const struct kernel_param *kp)
{
	int ret;
	u8 val;

	ret = kstrtou8(str, 0, &val);
	if (ret < 0)
		return ret;

	if (val > 1) {
		pr_err("Invalid block netlink value %u\n", val);
		return -EINVAL;
	}

	tcmu_netlink_blocked = val;
	return 0;
}