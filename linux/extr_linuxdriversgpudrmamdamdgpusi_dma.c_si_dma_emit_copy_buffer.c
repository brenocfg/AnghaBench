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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ib {int* ptr; int /*<<< orphan*/  length_dw; } ;

/* Variables and functions */
 int DMA_PACKET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_COPY ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_dma_emit_copy_buffer(struct amdgpu_ib *ib,
				       uint64_t src_offset,
				       uint64_t dst_offset,
				       uint32_t byte_count)
{
	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
					      1, 0, 0, byte_count);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = lower_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset) & 0xff;
	ib->ptr[ib->length_dw++] = upper_32_bits(src_offset) & 0xff;
}