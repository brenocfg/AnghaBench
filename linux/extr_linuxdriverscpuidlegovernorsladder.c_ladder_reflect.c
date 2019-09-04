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
struct ladder_device {int last_state_idx; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ladder_devices ; 
 struct ladder_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ladder_reflect(struct cpuidle_device *dev, int index)
{
	struct ladder_device *ldev = this_cpu_ptr(&ladder_devices);
	if (index > 0)
		ldev->last_state_idx = index;
}