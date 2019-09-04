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
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; } ;

/* Variables and functions */
 int MEID (int) ; 
 int PIPEID (int) ; 
 int QUEUEID (int) ; 
 int VMID (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  mmSRBM_GFX_CNTL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lock_srbm(struct kgd_dev *kgd, uint32_t mec, uint32_t pipe,
			uint32_t queue, uint32_t vmid)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t value = PIPEID(pipe) | MEID(mec) | VMID(vmid) | QUEUEID(queue);

	mutex_lock(&adev->srbm_mutex);
	WREG32(mmSRBM_GFX_CNTL, value);
}