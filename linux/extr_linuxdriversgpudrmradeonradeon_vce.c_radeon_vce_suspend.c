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
struct TYPE_2__ {int /*<<< orphan*/ * handles; int /*<<< orphan*/ * vcpu_bo; } ;
struct radeon_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int EINVAL ; 
 int RADEON_MAX_VCE_HANDLES ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

int radeon_vce_suspend(struct radeon_device *rdev)
{
	int i;

	if (rdev->vce.vcpu_bo == NULL)
		return 0;

	for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i)
		if (atomic_read(&rdev->vce.handles[i]))
			break;

	if (i == RADEON_MAX_VCE_HANDLES)
		return 0;

	/* TODO: suspending running encoding sessions isn't supported */
	return -EINVAL;
}