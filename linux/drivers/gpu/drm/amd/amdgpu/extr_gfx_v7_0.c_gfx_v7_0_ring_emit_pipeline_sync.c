#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int sync_seq; int gpu_addr; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; TYPE_2__* funcs; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_GFX ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SWITCH_BUFFER ; 
 int /*<<< orphan*/  PACKET3_WAIT_REG_MEM ; 
 int WAIT_REG_MEM_ENGINE (int) ; 
 int WAIT_REG_MEM_FUNCTION (int) ; 
 int WAIT_REG_MEM_MEM_SPACE (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx_v7_0_ring_emit_pipeline_sync(struct amdgpu_ring *ring)
{
	int usepfp = (ring->funcs->type == AMDGPU_RING_TYPE_GFX);
	uint32_t seq = ring->fence_drv.sync_seq;
	uint64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_write(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	amdgpu_ring_write(ring, (WAIT_REG_MEM_MEM_SPACE(1) | /* memory */
				 WAIT_REG_MEM_FUNCTION(3) | /* equal */
				 WAIT_REG_MEM_ENGINE(usepfp)));   /* pfp or me */
	amdgpu_ring_write(ring, addr & 0xfffffffc);
	amdgpu_ring_write(ring, upper_32_bits(addr) & 0xffffffff);
	amdgpu_ring_write(ring, seq);
	amdgpu_ring_write(ring, 0xffffffff);
	amdgpu_ring_write(ring, 4); /* poll interval */

	if (usepfp) {
		/* synce CE with ME to prevent CE fetch CEIB before context switch done */
		amdgpu_ring_write(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_write(ring, 0);
		amdgpu_ring_write(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		amdgpu_ring_write(ring, 0);
	}
}