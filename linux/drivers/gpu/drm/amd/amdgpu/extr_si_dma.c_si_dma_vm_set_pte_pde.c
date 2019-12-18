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
typedef  unsigned int uint32_t ;
struct amdgpu_ib {int* ptr; int /*<<< orphan*/  length_dw; } ;

/* Variables and functions */
 int AMDGPU_PTE_VALID ; 
 int DMA_PTE_PDE_PACKET (unsigned int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void si_dma_vm_set_pte_pde(struct amdgpu_ib *ib,
				     uint64_t pe,
				     uint64_t addr, unsigned count,
				     uint32_t incr, uint64_t flags)
{
	uint64_t value;
	unsigned ndw;

	while (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		if (flags & AMDGPU_PTE_VALID)
			value = addr;
		else
			value = 0;

		/* for physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = lower_32_bits(flags); /* mask */
		ib->ptr[ib->length_dw++] = upper_32_bits(flags);
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;
		pe += ndw * 4;
		addr += (ndw / 2) * incr;
		count -= ndw / 2;
	}
}