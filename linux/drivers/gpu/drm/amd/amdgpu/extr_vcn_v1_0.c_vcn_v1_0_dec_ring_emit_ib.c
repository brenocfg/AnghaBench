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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {unsigned int length_dw; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 unsigned int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,unsigned int) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_RBC_IB_VMID ; 
 int /*<<< orphan*/  mmUVD_RBC_IB_SIZE ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcn_v1_0_dec_ring_emit_ib(struct amdgpu_ring *ring,
					struct amdgpu_job *job,
					struct amdgpu_ib *ib,
					uint32_t flags)
{
	struct amdgpu_device *adev = ring->adev;
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_VMID), 0));
	amdgpu_ring_write(ring, vmid);

	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_64BIT_BAR_LOW), 0));
	amdgpu_ring_write(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH), 0));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_RBC_IB_SIZE), 0));
	amdgpu_ring_write(ring, ib->length_dw);
}