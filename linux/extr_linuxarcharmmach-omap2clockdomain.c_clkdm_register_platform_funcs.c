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
struct clkdm_ops {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 struct clkdm_ops* arch_clkdm ; 

int clkdm_register_platform_funcs(struct clkdm_ops *co)
{
	if (!co)
		return -EINVAL;

	if (arch_clkdm)
		return -EEXIST;

	arch_clkdm = co;

	return 0;
}