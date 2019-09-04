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
struct TYPE_2__ {int (* prepare ) () ;} ;

/* Variables and functions */
 TYPE_1__* pxa_cpu_pm_fns ; 
 int stub1 () ; 

int pxa_pm_prepare(void)
{
	int ret = 0;

	if (pxa_cpu_pm_fns && pxa_cpu_pm_fns->prepare)
		ret = pxa_cpu_pm_fns->prepare();

	return ret;
}