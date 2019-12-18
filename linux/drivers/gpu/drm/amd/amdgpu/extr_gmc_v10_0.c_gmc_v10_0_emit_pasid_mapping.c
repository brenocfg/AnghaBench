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
typedef  unsigned int uint32_t ;
struct amdgpu_ring {TYPE_1__* funcs; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ vmhub; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_GFXHUB_0 ; 
 int /*<<< orphan*/  OSSSYS ; 
 unsigned int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_wreg (struct amdgpu_ring*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mmIH_VMID_0_LUT ; 
 int /*<<< orphan*/  mmIH_VMID_0_LUT_MM ; 

__attribute__((used)) static void gmc_v10_0_emit_pasid_mapping(struct amdgpu_ring *ring, unsigned vmid,
					 unsigned pasid)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t reg;

	if (ring->funcs->vmhub == AMDGPU_GFXHUB_0)
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid;
	else
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT_MM) + vmid;

	amdgpu_ring_emit_wreg(ring, reg, pasid);
}