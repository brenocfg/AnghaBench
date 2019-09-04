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
 unsigned int MAX_DRIVES ; 
 unsigned int MAX_HWIFS ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,...) ; 

__attribute__((used)) static int ide_set_dev_param_mask(const char *s, const struct kernel_param *kp)
{
	unsigned int a, b, i, j = 1;
	unsigned int *dev_param_mask = (unsigned int *)kp->arg;

	/* controller . device (0 or 1) [ : 1 (set) | 0 (clear) ] */
	if (sscanf(s, "%u.%u:%u", &a, &b, &j) != 3 &&
	    sscanf(s, "%u.%u", &a, &b) != 2)
		return -EINVAL;

	i = a * MAX_DRIVES + b;

	if (i >= MAX_HWIFS * MAX_DRIVES || j > 1)
		return -EINVAL;

	if (j)
		*dev_param_mask |= (1 << i);
	else
		*dev_param_mask &= ~(1 << i);

	return 0;
}