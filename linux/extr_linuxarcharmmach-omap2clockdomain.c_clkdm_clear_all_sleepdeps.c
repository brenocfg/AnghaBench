#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clockdomain {int dummy; } ;
struct TYPE_2__ {int (* clkdm_clear_all_sleepdeps ) (struct clockdomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* arch_clkdm ; 
 int stub1 (struct clockdomain*) ; 

int clkdm_clear_all_sleepdeps(struct clockdomain *clkdm)
{
	if (!clkdm)
		return -EINVAL;

	if (!arch_clkdm || !arch_clkdm->clkdm_clear_all_sleepdeps)
		return -EINVAL;

	return arch_clkdm->clkdm_clear_all_sleepdeps(clkdm);
}