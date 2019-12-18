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
 int /*<<< orphan*/  SDMA_OP_FENCE ; 
 int /*<<< orphan*/  SDMA_OP_TRAP ; 
 int SDMA_PKT_FENCE_HEADER_MTYPE (int) ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_TRAP_INT_CONTEXT_INT_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void sdma_v5_0_ring_emit_fence(struct amdgpu_ring *ring, u64 addr, u64 seq,
				      unsigned flags)
{
	struct amdgpu_device *adev = ring->adev;
	bool write64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	/* write the fence */
	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE) |
			  SDMA_PKT_FENCE_HEADER_MTYPE(0x3)); /* Ucached(UC) */
	/* zero in first two bits */
	BUG_ON(addr & 0x3);
	amdgpu_ring_write(ring, lower_32_bits(addr));
	amdgpu_ring_write(ring, upper_32_bits(addr));
	amdgpu_ring_write(ring, lower_32_bits(seq));

	/* optionally write high bits as well */
	if (write64bit) {
		addr += 4;
		amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_FENCE) |
				  SDMA_PKT_FENCE_HEADER_MTYPE(0x3));
		/* zero in first two bits */
		BUG_ON(addr & 0x3);
		amdgpu_ring_write(ring, lower_32_bits(addr));
		amdgpu_ring_write(ring, upper_32_bits(addr));
		amdgpu_ring_write(ring, upper_32_bits(seq));
	}

	/* Interrupt not work fine on GFX10.1 model yet. Use fallback instead */
	if ((flags & AMDGPU_FENCE_FLAG_INT) && adev->pdev->device != 0x50) {
		/* generate an interrupt */
		amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_TRAP));
		amdgpu_ring_write(ring, SDMA_PKT_TRAP_INT_CONTEXT_INT_CONTEXT(0));
	}
}