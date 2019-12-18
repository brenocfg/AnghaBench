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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 unsigned int VCE_CMD_END ; 
 unsigned int VCE_CMD_FLUSH_TLB ; 
 unsigned int VCE_CMD_UPDATE_PTB ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,unsigned int) ; 

__attribute__((used)) static void vce_v3_0_emit_vm_flush(struct amdgpu_ring *ring,
				   unsigned int vmid, uint64_t pd_addr)
{
	amdgpu_ring_write(ring, VCE_CMD_UPDATE_PTB);
	amdgpu_ring_write(ring, vmid);
	amdgpu_ring_write(ring, pd_addr >> 12);

	amdgpu_ring_write(ring, VCE_CMD_FLUSH_TLB);
	amdgpu_ring_write(ring, vmid);
	amdgpu_ring_write(ring, VCE_CMD_END);
}