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
struct pwrdm_ops {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 struct pwrdm_ops* arch_pwrdm ; 

int pwrdm_register_platform_funcs(struct pwrdm_ops *po)
{
	if (!po)
		return -EINVAL;

	if (arch_pwrdm)
		return -EEXIST;

	arch_pwrdm = po;

	return 0;
}