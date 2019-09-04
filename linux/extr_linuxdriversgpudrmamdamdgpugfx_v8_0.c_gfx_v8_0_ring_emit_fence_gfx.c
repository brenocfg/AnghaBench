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
 unsigned int AMDGPU_FENCE_FLAG_INT ; 
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_TS_EVENT ; 
 int DATA_SEL (int) ; 
 int EOP_TCL1_ACTION_EN ; 
 int EOP_TC_ACTION_EN ; 
 int EOP_TC_WB_ACTION_EN ; 
 int EVENT_INDEX (int) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int INT_SEL (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE_EOP ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v8_0_ring_emit_fence_gfx(struct amdgpu_ring *ring, u64 addr,
					 u64 seq, unsigned flags)
{
	bool write64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool int_sel = flags & AMDGPU_FENCE_FLAG_INT;

	/* EVENT_WRITE_EOP - flush caches, send int */
	amdgpu_ring_write(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	amdgpu_ring_write(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EOP_TC_WB_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	amdgpu_ring_write(ring, addr & 0xfffffffc);
	amdgpu_ring_write(ring, (upper_32_bits(addr) & 0xffff) |
			  DATA_SEL(write64bit ? 2 : 1) | INT_SEL(int_sel ? 2 : 0));
	amdgpu_ring_write(ring, lower_32_bits(seq));
	amdgpu_ring_write(ring, upper_32_bits(seq));

}