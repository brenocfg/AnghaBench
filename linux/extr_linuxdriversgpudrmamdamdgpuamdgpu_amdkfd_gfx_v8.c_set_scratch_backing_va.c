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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_srbm (struct kgd_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSH_HIDDEN_PRIVATE_BASE_VMID ; 
 int /*<<< orphan*/  unlock_srbm (struct kgd_dev*) ; 

__attribute__((used)) static void set_scratch_backing_va(struct kgd_dev *kgd,
					uint64_t va, uint32_t vmid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;

	lock_srbm(kgd, 0, 0, 0, vmid);
	WREG32(mmSH_HIDDEN_PRIVATE_BASE_VMID, va);
	unlock_srbm(kgd);
}