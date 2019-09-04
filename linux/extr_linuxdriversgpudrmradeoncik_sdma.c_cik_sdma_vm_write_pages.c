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
typedef  int uint32_t ;
struct radeon_ib {int* ptr; int /*<<< orphan*/  length_dw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int R600_PTE_SYSTEM ; 
 int R600_PTE_VALID ; 
 int /*<<< orphan*/  SDMA_OPCODE_WRITE ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_WRITE_SUB_OPCODE_LINEAR ; 
 int radeon_vm_map_gart (struct radeon_device*,int) ; 
 void* upper_32_bits (int) ; 

void cik_sdma_vm_write_pages(struct radeon_device *rdev,
			     struct radeon_ib *ib,
			     uint64_t pe,
			     uint64_t addr, unsigned count,
			     uint32_t incr, uint32_t flags)
{
	uint64_t value;
	unsigned ndw;

	while (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		/* for non-physically contiguous pages (system) */
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_WRITE,
			SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
		ib->ptr[ib->length_dw++] = pe;
		ib->ptr[ib->length_dw++] = upper_32_bits(pe);
		ib->ptr[ib->length_dw++] = ndw;
		for (; ndw > 0; ndw -= 2, --count, pe += 8) {
			if (flags & R600_PTE_SYSTEM) {
				value = radeon_vm_map_gart(rdev, addr);
			} else if (flags & R600_PTE_VALID) {
				value = addr;
			} else {
				value = 0;
			}
			addr += incr;
			value |= flags;
			ib->ptr[ib->length_dw++] = value;
			ib->ptr[ib->length_dw++] = upper_32_bits(value);
		}
	}
}