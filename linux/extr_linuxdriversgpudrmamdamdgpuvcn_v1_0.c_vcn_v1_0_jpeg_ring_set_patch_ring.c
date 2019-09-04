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
struct amdgpu_ring {int* ring; int /*<<< orphan*/  gpu_addr; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* PACKETJ (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKETJ_TYPE0 ; 
 int /*<<< orphan*/  PACKETJ_TYPE2 ; 
 int /*<<< orphan*/  PACKETJ_TYPE3 ; 
 int /*<<< orphan*/  PACKETJ_TYPE6 ; 
 int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_JRBC_EXTERNAL_REG_BASE ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_COND_RD_TIMER ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_REF_DATA ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcn_v1_0_jpeg_ring_patch_wreg (struct amdgpu_ring*,int*,int,int) ; 

__attribute__((used)) static void vcn_v1_0_jpeg_ring_set_patch_ring(struct amdgpu_ring *ring, uint32_t ptr)
{
	struct amdgpu_device *adev = ring->adev;

	uint32_t reg, reg_offset, val, mask, i;

	// 1st: program mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW);
	reg_offset = (reg << 2);
	val = lower_32_bits(ring->gpu_addr);
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 2nd: program mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH);
	reg_offset = (reg << 2);
	val = upper_32_bits(ring->gpu_addr);
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 3rd to 5th: issue MEM_READ commands
	for (i = 0; i <= 2; i++) {
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE2);
		ring->ring[ptr++] = 0;
	}

	// 6th: program mmUVD_JRBC_RB_CNTL register to enable NO_FETCH and RPTR write ability
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x13;
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 7th: program mmUVD_JRBC_RB_REF_DATA
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_REF_DATA);
	reg_offset = (reg << 2);
	val = 0x1;
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);

	// 8th: issue conditional register read mmUVD_JRBC_RB_CNTL
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x1;
	mask = 0x1;

	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_COND_RD_TIMER), 0, 0, PACKETJ_TYPE0);
	ring->ring[ptr++] = 0x01400200;
	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_REF_DATA), 0, 0, PACKETJ_TYPE0);
	ring->ring[ptr++] = val;
	ring->ring[ptr++] = PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0);
	if (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
		((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) {
		ring->ring[ptr++] = 0;
		ring->ring[ptr++] = PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE3);
	} else {
		ring->ring[ptr++] = reg_offset;
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE3);
	}
	ring->ring[ptr++] = mask;

	//9th to 21st: insert no-op
	for (i = 0; i <= 12; i++) {
		ring->ring[ptr++] = PACKETJ(0, 0, 0, PACKETJ_TYPE6);
		ring->ring[ptr++] = 0;
	}

	//22nd: reset mmUVD_JRBC_RB_RPTR
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_RPTR);
	reg_offset = (reg << 2);
	val = 0;
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);

	//23rd: program mmUVD_JRBC_RB_CNTL to disable no_fetch
	reg = SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_RB_CNTL);
	reg_offset = (reg << 2);
	val = 0x12;
	vcn_v1_0_jpeg_ring_patch_wreg(ring, &ptr, reg_offset, val);
}