#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_ps; int /*<<< orphan*/ * ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  radeon_dpm_print_power_state (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_dpm_print_power_states(struct radeon_device *rdev)
{
	int i;

	for (i = 0; i < rdev->pm.dpm.num_ps; i++) {
		printk("== power state %d ==\n", i);
		radeon_dpm_print_power_state(rdev, &rdev->pm.dpm.ps[i]);
	}
}