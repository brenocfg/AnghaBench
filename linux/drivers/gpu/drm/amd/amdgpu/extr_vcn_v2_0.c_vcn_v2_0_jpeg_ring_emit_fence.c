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
typedef  int u64 ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 unsigned int AMDGPU_FENCE_FLAG_64BIT ; 
 int /*<<< orphan*/  JRBC_DEC_EXTERNAL_REG_WRITE_ADDR ; 
 int PACKETJ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKETJ_CONDITION_CHECK0 ; 
 int /*<<< orphan*/  PACKETJ_TYPE0 ; 
 int /*<<< orphan*/  PACKETJ_TYPE4 ; 
 int /*<<< orphan*/  PACKETJ_TYPE7 ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_JPEG_GPCOM_DATA0_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_JPEG_GPCOM_DATA1_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_HIGH_INTERNAL_OFFSET ; 
 int /*<<< orphan*/  mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_LOW_INTERNAL_OFFSET ; 
 int upper_32_bits (int) ; 

void vcn_v2_0_jpeg_ring_emit_fence(struct amdgpu_ring *ring, u64 addr, u64 seq,
				unsigned flags)
{
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_write(ring, PACKETJ(mmUVD_JPEG_GPCOM_DATA0_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, seq);

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_JPEG_GPCOM_DATA1_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, seq);

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_LOW_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, lower_32_bits(addr));

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_HIGH_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, upper_32_bits(addr));

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, 0x8);

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET,
		0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE4));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring,	PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, 0x3fbc);

	amdgpu_ring_write(ring, PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_write(ring, 0x1);

	amdgpu_ring_write(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE7));
	amdgpu_ring_write(ring, 0);
}