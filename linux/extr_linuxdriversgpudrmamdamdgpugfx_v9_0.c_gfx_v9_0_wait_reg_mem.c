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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_WAIT_REG_MEM ; 
 int WAIT_REG_MEM_ENGINE (int) ; 
 int WAIT_REG_MEM_FUNCTION (int) ; 
 int WAIT_REG_MEM_MEM_SPACE (int) ; 
 int WAIT_REG_MEM_OPERATION (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void gfx_v9_0_wait_reg_mem(struct amdgpu_ring *ring, int eng_sel,
				  int mem_space, int opt, uint32_t addr0,
				  uint32_t addr1, uint32_t ref, uint32_t mask,
				  uint32_t inv)
{
	amdgpu_ring_write(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_write(ring,
				 /* memory (1) or register (0) */
				 (WAIT_REG_MEM_MEM_SPACE(mem_space) |
				 WAIT_REG_MEM_OPERATION(opt) | /* wait */
				 WAIT_REG_MEM_FUNCTION(3) |  /* equal */
				 WAIT_REG_MEM_ENGINE(eng_sel)));

	if (mem_space)
		BUG_ON(addr0 & 0x3); /* Dword align */
	amdgpu_ring_write(ring, addr0);
	amdgpu_ring_write(ring, addr1);
	amdgpu_ring_write(ring, ref);
	amdgpu_ring_write(ring, mask);
	amdgpu_ring_write(ring, inv); /* poll interval */
}