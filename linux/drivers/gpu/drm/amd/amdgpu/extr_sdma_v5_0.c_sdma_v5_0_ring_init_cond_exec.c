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
 int /*<<< orphan*/  SDMA_OP_COND_EXE ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned sdma_v5_0_ring_init_cond_exec(struct amdgpu_ring *ring)
{
	unsigned ret;

	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_COND_EXE));
	amdgpu_ring_write(ring, lower_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_write(ring, upper_32_bits(ring->cond_exe_gpu_addr));
	amdgpu_ring_write(ring, 1);
	ret = ring->wptr & ring->buf_mask;/* this is the offset we need patch later */
	amdgpu_ring_write(ring, 0x55aa55aa);/* insert dummy here and patch it later */

	return ret;
}