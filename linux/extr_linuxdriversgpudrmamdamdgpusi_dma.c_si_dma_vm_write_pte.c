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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct amdgpu_ib {int /*<<< orphan*/  length_dw; void** ptr; } ;

/* Variables and functions */
 void* DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DMA_PACKET_WRITE ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_dma_vm_write_pte(struct amdgpu_ib *ib, uint64_t pe,
				uint64_t value, unsigned count,
				uint32_t incr)
{
	unsigned ndw = count * 2;

	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 0, ndw);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	for (; ndw > 0; ndw -= 2) {
		ib->ptr[ib->length_dw++] = lower_32_bits(value);
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		value += incr;
	}
}