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
struct TYPE_2__ {int enabled; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int radeon_asic_vm_init (struct radeon_device*) ; 

int radeon_vm_manager_init(struct radeon_device *rdev)
{
	int r;

	if (!rdev->vm_manager.enabled) {
		r = radeon_asic_vm_init(rdev);
		if (r)
			return r;

		rdev->vm_manager.enabled = true;
	}
	return 0;
}