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
struct amdgpu_ring {int /*<<< orphan*/  gpu_addr; struct amdgpu_device* adev; } ;
struct amdgpu_ib {int length_dw; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int PACKETJ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKETJ_CONDITION_CHECK0 ; 
 int /*<<< orphan*/  PACKETJ_CONDITION_CHECK3 ; 
 int /*<<< orphan*/  PACKETJ_TYPE0 ; 
 int /*<<< orphan*/  PACKETJ_TYPE2 ; 
 int /*<<< orphan*/  PACKETJ_TYPE3 ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_JRBC_IB_SIZE ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_COND_RD_TIMER ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_REF_DATA ; 
 int /*<<< orphan*/  mmUVD_JRBC_STATUS ; 
 int /*<<< orphan*/  mmUVD_LMI_JPEG_VMID ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_IB_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_IB_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_IB_VMID ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vcn_v1_0_jpeg_ring_emit_ib(struct amdgpu_ring *ring,
				  struct amdgpu_ib *ib,
				  unsigned vmid, bool ctx_switch)
{
	struct amdgpu_device *adev = ring->adev;

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_IB_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, (vmid | (vmid << 4)));

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JPEG_VMID), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, (vmid | (vmid << 4)));

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_IB_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, lower_32_bits(ib->gpu_addr));

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_IB_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr));

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_IB_SIZE), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, ib->length_dw);

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, lower_32_bits(ring->gpu_addr));

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, upper_32_bits(ring->gpu_addr));

	amdgpu_ring_write(ring,
		PACKETJ(0, 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE2));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, 0x01400200);

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, 0x2);

	amdgpu_ring_write(ring,
		PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_STATUS), 0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE3));
	amdgpu_ring_write(ring, 0x2);
}