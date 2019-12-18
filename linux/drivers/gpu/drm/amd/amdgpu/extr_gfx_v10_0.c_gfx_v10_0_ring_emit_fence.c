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
typedef  int u64 ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 unsigned int AMDGPU_FENCE_FLAG_64BIT ; 
 unsigned int AMDGPU_FENCE_FLAG_INT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_TS_EVENT ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_RELEASE_MEM ; 
 int PACKET3_RELEASE_MEM_CACHE_POLICY (int) ; 
 int PACKET3_RELEASE_MEM_DATA_SEL (int) ; 
 int PACKET3_RELEASE_MEM_EVENT_INDEX (int) ; 
 int PACKET3_RELEASE_MEM_EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3_RELEASE_MEM_GCR_GL2_WB ; 
 int PACKET3_RELEASE_MEM_GCR_GLM_INV ; 
 int PACKET3_RELEASE_MEM_GCR_GLM_WB ; 
 int PACKET3_RELEASE_MEM_GCR_SEQ ; 
 int PACKET3_RELEASE_MEM_INT_SEL (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v10_0_ring_emit_fence(struct amdgpu_ring *ring, u64 addr,
				     u64 seq, unsigned flags)
{
	struct amdgpu_device *adev = ring->adev;
	bool write64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool int_sel = flags & AMDGPU_FENCE_FLAG_INT;

	/* Interrupt not work fine on GFX10.1 model yet. Use fallback instead */
	if (adev->pdev->device == 0x50)
		int_sel = false;

	/* RELEASE_MEM - flush caches, send int */
	amdgpu_ring_write(ring, PACKET3(PACKET3_RELEASE_MEM, 6));
	amdgpu_ring_write(ring, (PACKET3_RELEASE_MEM_GCR_SEQ |
				 PACKET3_RELEASE_MEM_GCR_GL2_WB |
				 PACKET3_RELEASE_MEM_GCR_GLM_INV | /* must be set with GLM_WB */
				 PACKET3_RELEASE_MEM_GCR_GLM_WB |
				 PACKET3_RELEASE_MEM_CACHE_POLICY(3) |
				 PACKET3_RELEASE_MEM_EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 PACKET3_RELEASE_MEM_EVENT_INDEX(5)));
	amdgpu_ring_write(ring, (PACKET3_RELEASE_MEM_DATA_SEL(write64bit ? 2 : 1) |
				 PACKET3_RELEASE_MEM_INT_SEL(int_sel ? 2 : 0)));

	/*
	 * the address should be Qword aligned if 64bit write, Dword
	 * aligned if only send 32bit data low (discard data high)
	 */
	if (write64bit)
		BUG_ON(addr & 0x7);
	else
		BUG_ON(addr & 0x3);
	amdgpu_ring_write(ring, lower_32_bits(addr));
	amdgpu_ring_write(ring, upper_32_bits(addr));
	amdgpu_ring_write(ring, lower_32_bits(seq));
	amdgpu_ring_write(ring, upper_32_bits(seq));
	amdgpu_ring_write(ring, 0);
}