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
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int HDP_MEM_COHERENCY_FLUSH_CNTL ; 
 int PACKET0 (int,int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_PFP_SYNC_ME ; 
 int /*<<< orphan*/  PACKET3_WAIT_REG_MEM ; 
 unsigned int VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 int VM_INVALIDATE_REQUEST ; 
 int WAIT_REG_MEM_ENGINE (int /*<<< orphan*/ ) ; 
 int WAIT_REG_MEM_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void cayman_vm_flush(struct radeon_device *rdev, struct radeon_ring *ring,
		     unsigned vm_id, uint64_t pd_addr)
{
	radeon_ring_write(ring, PACKET0(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2), 0));
	radeon_ring_write(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_write(ring, PACKET0(HDP_MEM_COHERENCY_FLUSH_CNTL, 0));
	radeon_ring_write(ring, 0x1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_write(ring, PACKET0(VM_INVALIDATE_REQUEST, 0));
	radeon_ring_write(ring, 1 << vm_id);

	/* wait for the invalidate to complete */
	radeon_ring_write(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_write(ring, (WAIT_REG_MEM_FUNCTION(0) |  /* always */
				 WAIT_REG_MEM_ENGINE(0))); /* me */
	radeon_ring_write(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0); /* ref */
	radeon_ring_write(ring, 0); /* mask */
	radeon_ring_write(ring, 0x20); /* poll interval */

	/* sync PFP to ME, otherwise we might get invalid PFP reads */
	radeon_ring_write(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
	radeon_ring_write(ring, 0x0);
}