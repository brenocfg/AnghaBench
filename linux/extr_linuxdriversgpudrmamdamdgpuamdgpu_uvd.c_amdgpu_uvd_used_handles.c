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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {unsigned int max_handles; int /*<<< orphan*/ * handles; } ;
struct amdgpu_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

uint32_t amdgpu_uvd_used_handles(struct amdgpu_device *adev)
{
	unsigned i;
	uint32_t used_handles = 0;

	for (i = 0; i < adev->uvd.max_handles; ++i) {
		/*
		 * Handles can be freed in any order, and not
		 * necessarily linear. So we need to count
		 * all non-zero handles.
		 */
		if (atomic_read(&adev->uvd.handles[i]))
			used_handles++;
	}

	return used_handles;
}