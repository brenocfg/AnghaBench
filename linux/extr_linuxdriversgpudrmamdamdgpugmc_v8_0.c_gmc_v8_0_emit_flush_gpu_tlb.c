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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_emit_wreg (struct amdgpu_ring*,scalar_t__,int) ; 
 scalar_t__ mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 scalar_t__ mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR ; 
 scalar_t__ mmVM_INVALIDATE_REQUEST ; 

__attribute__((used)) static uint64_t gmc_v8_0_emit_flush_gpu_tlb(struct amdgpu_ring *ring,
					    unsigned vmid, uint64_t pd_addr)
{
	uint32_t reg;

	if (vmid < 8)
		reg = mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR + vmid;
	else
		reg = mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + vmid - 8;
	amdgpu_ring_emit_wreg(ring, reg, pd_addr >> 12);

	/* bits 0-15 are the VM contexts0-15 */
	amdgpu_ring_emit_wreg(ring, mmVM_INVALIDATE_REQUEST, 1 << vmid);

	return pd_addr;
}