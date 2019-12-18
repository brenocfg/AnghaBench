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
struct amdgpu_ring {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ fw_version; int num_rings; int /*<<< orphan*/  irq; struct amdgpu_ring* ring; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 scalar_t__ FW_52_8_3 ; 
 int VCE_V3_0_DATA_SIZE ; 
 scalar_t__ VCE_V3_0_FW_SIZE ; 
 int VCE_V3_0_STACK_SIZE ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_VCE_TRAP ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amdgpu_vce_entity_init (struct amdgpu_device*) ; 
 int amdgpu_vce_resume (struct amdgpu_device*) ; 
 int amdgpu_vce_sw_init (struct amdgpu_device*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vce_v3_0_sw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring;
	int r, i;

	/* VCE */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_VCE_TRAP, &adev->vce.irq);
	if (r)
		return r;

	r = amdgpu_vce_sw_init(adev, VCE_V3_0_FW_SIZE +
		(VCE_V3_0_STACK_SIZE + VCE_V3_0_DATA_SIZE) * 2);
	if (r)
		return r;

	/* 52.8.3 required for 3 ring support */
	if (adev->vce.fw_version < FW_52_8_3)
		adev->vce.num_rings = 2;

	r = amdgpu_vce_resume(adev);
	if (r)
		return r;

	for (i = 0; i < adev->vce.num_rings; i++) {
		ring = &adev->vce.ring[i];
		sprintf(ring->name, "vce%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vce.irq, 0);
		if (r)
			return r;
	}

	r = amdgpu_vce_entity_init(adev);

	return r;
}