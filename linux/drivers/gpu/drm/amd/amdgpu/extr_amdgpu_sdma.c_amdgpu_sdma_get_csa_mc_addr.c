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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_CSA_SDMA_OFFSET ; 
 int AMDGPU_CSA_SDMA_SIZE ; 
 scalar_t__ amdgpu_csa_vaddr (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_mcbp ; 
 int amdgpu_sdma_get_index_from_ring (struct amdgpu_ring*,int*) ; 

uint64_t amdgpu_sdma_get_csa_mc_addr(struct amdgpu_ring *ring,
				     unsigned vmid)
{
	struct amdgpu_device *adev = ring->adev;
	uint64_t csa_mc_addr;
	uint32_t index = 0;
	int r;

	if (vmid == 0 || !amdgpu_mcbp)
		return 0;

	r = amdgpu_sdma_get_index_from_ring(ring, &index);

	if (r || index > 31)
		csa_mc_addr = 0;
	else
		csa_mc_addr = amdgpu_csa_vaddr(adev) +
			AMDGPU_CSA_SDMA_OFFSET +
			index * AMDGPU_CSA_SDMA_SIZE;

	return csa_mc_addr;
}