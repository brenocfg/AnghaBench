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
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  mmUVD_CONTEXT_ID ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void uvd_v4_2_ring_emit_fence(struct amdgpu_ring *ring, u64 addr, u64 seq,
				     unsigned flags)
{
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_write(ring, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_ring_write(ring, seq);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_write(ring, addr & 0xffffffff);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_write(ring, upper_32_bits(addr) & 0xff);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_write(ring, 0);

	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_write(ring, 2);
}