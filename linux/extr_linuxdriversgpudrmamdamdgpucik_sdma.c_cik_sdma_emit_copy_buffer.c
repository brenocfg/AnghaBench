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
typedef  void* uint32_t ;
struct amdgpu_ib {int /*<<< orphan*/  length_dw; void** ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_COPY_SUB_OPCODE_LINEAR ; 
 int /*<<< orphan*/  SDMA_OPCODE_COPY ; 
 void* SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_sdma_emit_copy_buffer(struct amdgpu_ib *ib,
				      uint64_t src_offset,
				      uint64_t dst_offset,
				      uint32_t byte_count)
{
	ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY, SDMA_COPY_SUB_OPCODE_LINEAR, 0);
	ib->ptr[ib->length_dw++] = byte_count;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset);
}