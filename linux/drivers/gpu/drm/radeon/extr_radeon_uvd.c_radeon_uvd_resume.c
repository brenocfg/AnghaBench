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
struct TYPE_3__ {void* cpu_addr; int /*<<< orphan*/ * vcpu_bo; } ;
struct radeon_device {TYPE_2__* uvd_fw; TYPE_1__ uvd; } ;
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int radeon_bo_size (int /*<<< orphan*/ *) ; 

int radeon_uvd_resume(struct radeon_device *rdev)
{
	unsigned size;
	void *ptr;

	if (rdev->uvd.vcpu_bo == NULL)
		return -EINVAL;

	memcpy(rdev->uvd.cpu_addr, rdev->uvd_fw->data, rdev->uvd_fw->size);

	size = radeon_bo_size(rdev->uvd.vcpu_bo);
	size -= rdev->uvd_fw->size;

	ptr = rdev->uvd.cpu_addr;
	ptr += rdev->uvd_fw->size;

	memset(ptr, 0, size);

	return 0;
}