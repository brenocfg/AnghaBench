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
struct TYPE_2__ {int enabled; int /*<<< orphan*/ * active; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int RADEON_NUM_VM ; 
 int /*<<< orphan*/  radeon_asic_vm_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_unref (int /*<<< orphan*/ *) ; 

void radeon_vm_manager_fini(struct radeon_device *rdev)
{
	int i;

	if (!rdev->vm_manager.enabled)
		return;

	for (i = 0; i < RADEON_NUM_VM; ++i)
		radeon_fence_unref(&rdev->vm_manager.active[i]);
	radeon_asic_vm_fini(rdev);
	rdev->vm_manager.enabled = false;
}