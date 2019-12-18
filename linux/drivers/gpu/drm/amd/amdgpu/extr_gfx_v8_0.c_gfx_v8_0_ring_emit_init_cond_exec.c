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
struct amdgpu_ring {unsigned int wptr; unsigned int buf_mask; int /*<<< orphan*/  cond_exe_gpu_addr; } ;

/* Variables and functions */
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_COND_EXEC ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned gfx_v8_0_ring_emit_init_cond_exec(struct amdgpu_ring *ring)
{
	unsigned ret;

	amdgpu_ring_write(ring, PACKET3(PACKET3_COND_EXEC, 3));
	amdgpu_ring_write(ring, lower_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_write(ring, upper_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_write(ring, 0); /* discard following DWs if *cond_exec_gpu_addr==0 */
	ret = ring->wptr & ring->buf_mask;
	amdgpu_ring_write(ring, 0x55aa55aa); /* patch dummy value later */
	return ret;
}