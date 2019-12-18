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
 unsigned int DMA_PTE_PDE_PACKET (unsigned int) ; 
 int R600_PTE_VALID ; 
 int upper_32_bits (unsigned int) ; 

void cayman_dma_vm_set_pages(struct radeon_device *rdev,
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

		if (flags & R600_PTE_VALID)
			value = addr;
		else
			value = 0;

		/* for physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = flags; /* mask */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;

		pe += ndw * 4;
		addr += (ndw / 2) * incr;
		count -= ndw / 2;
	}
}