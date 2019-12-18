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
struct radeon_ib {int* ptr; int /*<<< orphan*/  length_dw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DMA_PACKET_COPY ; 
 void* lower_32_bits (unsigned int) ; 
 int upper_32_bits (unsigned int) ; 

void cayman_dma_vm_copy_pages(struct radeon_device *rdev,
			      struct radeon_ib *ib,
			      uint64_t pe, uint64_t src,
			      unsigned count)
{
	unsigned ndw;

	while (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
						      0, 0, ndw);
		ib->ptr[ib->length_dw++] = lower_32_bits(pe);
		ib->ptr[ib->length_dw++] = lower_32_bits(src);
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = upper_32_bits(src) & 0xff;

		pe += ndw * 4;
		src += ndw * 4;
		count -= ndw / 2;
	}
}