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
typedef  int u32 ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_ib {unsigned int length_dw; int gpu_addr; } ;

/* Variables and functions */
 unsigned int INDIRECT_BUFFER_VALID ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v8_0_ring_emit_ib_compute(struct amdgpu_ring *ring,
					  struct amdgpu_ib *ib,
					  unsigned vmid, bool ctx_switch)
{
	u32 control = INDIRECT_BUFFER_VALID | ib->length_dw | (vmid << 24);

	amdgpu_ring_write(ring, PACKET3(PACKET3_INDIRECT_BUFFER, 2));
	amdgpu_ring_write(ring,
#ifdef __BIG_ENDIAN
				(2 << 0) |
#endif
				(ib->gpu_addr & 0xFFFFFFFC));
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	amdgpu_ring_write(ring, control);
}