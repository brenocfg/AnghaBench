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
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;
struct radeon_ib {unsigned int* ptr; int /*<<< orphan*/  length_dw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int R600_PTE_VALID ; 
 int /*<<< orphan*/  SDMA_OPCODE_GENERATE_PTE_PDE ; 
 unsigned int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* upper_32_bits (unsigned int) ; 

void cik_sdma_vm_set_pages(struct radeon_device *rdev,
			   struct radeon_ib *ib,
			   uint64_t pe,
			   uint64_t addr, unsigned count,
			   uint32_t incr, uint32_t flags)
{
	uint64_t value;
	unsigned ndw;

	while (count) {
		ndw = count;
		if (ndw > 0x7FFFF)
			ndw = 0x7FFFF;

		if (flags & R600_PTE_VALID)
			value = addr;
		else
			value = 0;

		/* for physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_GENERATE_PTE_PDE, 0, 0);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe);
		ib->ptr[ib->length_dw++] = flags; /* mask */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = ndw; /* number of entries */

		pe += ndw * 8;
		addr += ndw * incr;
		count -= ndw;
	}
}