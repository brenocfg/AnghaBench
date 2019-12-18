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
struct common_firmware_header {int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vcpu_bo; TYPE_1__* fw; } ;
struct amdgpu_device {TYPE_2__ vce; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int amdgpu_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ *) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (void*,scalar_t__,scalar_t__) ; 

int amdgpu_vce_resume(struct amdgpu_device *adev)
{
	void *cpu_addr;
	const struct common_firmware_header *hdr;
	unsigned offset;
	int r;

	if (adev->vce.vcpu_bo == NULL)
		return -EINVAL;

	r = amdgpu_bo_reserve(adev->vce.vcpu_bo, false);
	if (r) {
		dev_err(adev->dev, "(%d) failed to reserve VCE bo\n", r);
		return r;
	}

	r = amdgpu_bo_kmap(adev->vce.vcpu_bo, &cpu_addr);
	if (r) {
		amdgpu_bo_unreserve(adev->vce.vcpu_bo);
		dev_err(adev->dev, "(%d) VCE map failed\n", r);
		return r;
	}

	hdr = (const struct common_firmware_header *)adev->vce.fw->data;
	offset = le32_to_cpu(hdr->ucode_array_offset_bytes);
	memcpy_toio(cpu_addr, adev->vce.fw->data + offset,
		    adev->vce.fw->size - offset);

	amdgpu_bo_kunmap(adev->vce.vcpu_bo);

	amdgpu_bo_unreserve(adev->vce.vcpu_bo);

	return 0;
}