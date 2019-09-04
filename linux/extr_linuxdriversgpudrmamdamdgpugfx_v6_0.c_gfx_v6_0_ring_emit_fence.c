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
 int CP_EOP_DONE_DATA_CNTL__DATA_SEL__SHIFT ; 
 int CP_EOP_DONE_DATA_CNTL__INT_SEL__SHIFT ; 
 int EVENT_INDEX (int) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE_EOP ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 int PACKET3_SH_ICACHE_ACTION_ENA ; 
 int PACKET3_SH_KCACHE_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 int PACKET3_TCL1_ACTION_ENA ; 
 int PACKET3_TC_ACTION_ENA ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int mmCP_COHER_CNTL2 ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v6_0_ring_emit_fence(struct amdgpu_ring *ring, u64 addr,
				     u64 seq, unsigned flags)
{
	bool write64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	bool int_sel = flags & AMDGPU_FENCE_FLAG_INT;
	/* flush read cache over gart */
	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
	amdgpu_ring_write(ring, (mmCP_COHER_CNTL2 - PACKET3_SET_CONFIG_REG_START));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	amdgpu_ring_write(ring, PACKET3_TCL1_ACTION_ENA |
			  PACKET3_TC_ACTION_ENA |
			  PACKET3_SH_KCACHE_ACTION_ENA |
			  PACKET3_SH_ICACHE_ACTION_ENA);
	amdgpu_ring_write(ring, 0xFFFFFFFF);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 10); /* poll interval */
	/* EVENT_WRITE_EOP - flush caches, send int */
	amdgpu_ring_write(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	amdgpu_ring_write(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) | EVENT_INDEX(5));
	amdgpu_ring_write(ring, addr & 0xfffffffc);
	amdgpu_ring_write(ring, (upper_32_bits(addr) & 0xffff) |
				((write64bit ? 2 : 1) << CP_EOP_DONE_DATA_CNTL__DATA_SEL__SHIFT) |
				((int_sel ? 2 : 0) << CP_EOP_DONE_DATA_CNTL__INT_SEL__SHIFT));
	amdgpu_ring_write(ring, lower_32_bits(seq));
	amdgpu_ring_write(ring, upper_32_bits(seq));
}