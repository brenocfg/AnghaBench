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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_SRBM_WRITE ; 
 int /*<<< orphan*/  SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_sdma_ring_emit_wreg(struct amdgpu_ring *ring,
				    uint32_t reg, uint32_t val)
{
	amdgpu_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	amdgpu_ring_write(ring, reg);
	amdgpu_ring_write(ring, val);
}