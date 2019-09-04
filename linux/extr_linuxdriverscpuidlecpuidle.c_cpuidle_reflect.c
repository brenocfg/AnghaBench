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
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reflect ) (struct cpuidle_device*,int) ;} ;

/* Variables and functions */
 TYPE_1__* cpuidle_curr_governor ; 
 int /*<<< orphan*/  stub1 (struct cpuidle_device*,int) ; 

void cpuidle_reflect(struct cpuidle_device *dev, int index)
{
	if (cpuidle_curr_governor->reflect && index >= 0)
		cpuidle_curr_governor->reflect(dev, index);
}