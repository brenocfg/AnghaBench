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
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* boot_ps; struct amdgpu_ps* requested_ps; struct amdgpu_ps* current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 

void amdgpu_dpm_print_ps_status(struct amdgpu_device *adev,
				struct amdgpu_ps *rps)
{
	printk("\tstatus:");
	if (rps == adev->pm.dpm.current_ps)
		pr_cont(" c");
	if (rps == adev->pm.dpm.requested_ps)
		pr_cont(" r");
	if (rps == adev->pm.dpm.boot_ps)
		pr_cont(" b");
	pr_cont("\n");
}