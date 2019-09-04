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
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_SRBM_WRITE ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void si_dma_ring_emit_wreg(struct amdgpu_ring *ring,
				  uint32_t reg, uint32_t val)
{
	amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0, 0));
	amdgpu_ring_write(ring, (0xf << 16) | reg);
	amdgpu_ring_write(ring, val);
}