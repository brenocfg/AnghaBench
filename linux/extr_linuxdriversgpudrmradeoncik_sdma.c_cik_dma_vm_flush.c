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
typedef  int u32 ;
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_POLL_REG_MEM ; 
 int /*<<< orphan*/  SDMA_OPCODE_SRBM_WRITE ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SDMA_POLL_REG_MEM_EXTRA_FUNC (int /*<<< orphan*/ ) ; 
 int SDMA_POLL_REG_MEM_EXTRA_OP (int /*<<< orphan*/ ) ; 
 int SH_MEM_APE1_BASE ; 
 int SH_MEM_APE1_LIMIT ; 
 int SH_MEM_BASES ; 
 int SH_MEM_CONFIG ; 
 int SRBM_GFX_CNTL ; 
 int VMID (unsigned int) ; 
 unsigned int VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 unsigned int VM_CONTEXT8_PAGE_TABLE_BASE_ADDR ; 
 int VM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  cik_sdma_hdp_flush_ring_emit (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void cik_dma_vm_flush(struct radeon_device *rdev, struct radeon_ring *ring,
		      unsigned vm_id, uint64_t pd_addr)
{
	u32 extra_bits = (SDMA_POLL_REG_MEM_EXTRA_OP(0) |
			  SDMA_POLL_REG_MEM_EXTRA_FUNC(0)); /* always */

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	if (vm_id < 8) {
		radeon_ring_write(ring, (VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2);
	} else {
		radeon_ring_write(ring, (VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((vm_id - 8) << 2)) >> 2);
	}
	radeon_ring_write(ring, pd_addr >> 12);

	/* update SH_MEM_* regs */
	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_write(ring, VMID(vm_id));

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SH_MEM_BASES >> 2);
	radeon_ring_write(ring, 0);

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SH_MEM_CONFIG >> 2);
	radeon_ring_write(ring, 0);

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SH_MEM_APE1_BASE >> 2);
	radeon_ring_write(ring, 1);

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SH_MEM_APE1_LIMIT >> 2);
	radeon_ring_write(ring, 0);

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_write(ring, VMID(0));

	/* flush HDP */
	cik_sdma_hdp_flush_ring_emit(rdev, ring->idx);

	/* flush TLB */
	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_write(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_write(ring, 1 << vm_id);

	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_POLL_REG_MEM, 0, extra_bits));
	radeon_ring_write(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 0); /* reference */
	radeon_ring_write(ring, 0); /* mask */
	radeon_ring_write(ring, (0xfff << 16) | 10); /* retry count, poll interval */
}