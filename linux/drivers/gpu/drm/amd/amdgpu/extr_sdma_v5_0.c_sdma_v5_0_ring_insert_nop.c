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
typedef  int uint32_t ;
struct amdgpu_sdma_instance {scalar_t__ burst_nop; } ;
struct amdgpu_ring {TYPE_1__* funcs; } ;
struct TYPE_2__ {int nop; } ;

/* Variables and functions */
 int SDMA_PKT_NOP_HEADER_COUNT (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 struct amdgpu_sdma_instance* amdgpu_sdma_get_instance_from_ring (struct amdgpu_ring*) ; 

__attribute__((used)) static void sdma_v5_0_ring_insert_nop(struct amdgpu_ring *ring, uint32_t count)
{
	struct amdgpu_sdma_instance *sdma = amdgpu_sdma_get_instance_from_ring(ring);
	int i;

	for (i = 0; i < count; i++)
		if (sdma && sdma->burst_nop && (i == 0))
			amdgpu_ring_write(ring, ring->funcs->nop |
				SDMA_PKT_NOP_HEADER_COUNT(count - 1));
		else
			amdgpu_ring_write(ring, ring->funcs->nop);
}