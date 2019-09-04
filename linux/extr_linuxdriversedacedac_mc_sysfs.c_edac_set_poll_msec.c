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
 int /*<<< orphan*/  edac_mc_reset_delay_period (unsigned long) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int edac_set_poll_msec(const char *val, const struct kernel_param *kp)
{
	unsigned long l;
	int ret;

	if (!val)
		return -EINVAL;

	ret = kstrtoul(val, 0, &l);
	if (ret)
		return ret;

	if (l < 1000)
		return -EINVAL;

	*((unsigned long *)kp->arg) = l;

	/* notify edac_mc engine to reset the poll period */
	edac_mc_reset_delay_period(l);

	return 0;
}