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
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_2__ {int (* valid ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* puv3_cpu_pm_fns ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_pm_valid(suspend_state_t state)
{
	if (puv3_cpu_pm_fns)
		return puv3_cpu_pm_fns->valid(state);

	return -EINVAL;
}