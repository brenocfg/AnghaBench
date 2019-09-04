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
struct TYPE_4__ {int /*<<< orphan*/ * vcpu_bo; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ vce; TYPE_1__* vce_fw; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ CHIP_BONAIRE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  radeon_bo_kunmap (int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 int vce_v1_0_load_fw (struct radeon_device*,void*) ; 

int radeon_vce_resume(struct radeon_device *rdev)
{
	void *cpu_addr;
	int r;

	if (rdev->vce.vcpu_bo == NULL)
		return -EINVAL;

	r = radeon_bo_reserve(rdev->vce.vcpu_bo, false);
	if (r) {
		dev_err(rdev->dev, "(%d) failed to reserve VCE bo\n", r);
		return r;
	}

	r = radeon_bo_kmap(rdev->vce.vcpu_bo, &cpu_addr);
	if (r) {
		radeon_bo_unreserve(rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) VCE map failed\n", r);
		return r;
	}

	memset(cpu_addr, 0, radeon_bo_size(rdev->vce.vcpu_bo));
	if (rdev->family < CHIP_BONAIRE)
		r = vce_v1_0_load_fw(rdev, cpu_addr);
	else
		memcpy(cpu_addr, rdev->vce_fw->data, rdev->vce_fw->size);

	radeon_bo_kunmap(rdev->vce.vcpu_bo);

	radeon_bo_unreserve(rdev->vce.vcpu_bo);

	return r;
}