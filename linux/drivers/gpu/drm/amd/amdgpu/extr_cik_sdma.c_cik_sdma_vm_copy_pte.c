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
struct amdgpu_ib {unsigned int* ptr; int /*<<< orphan*/  length_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_COPY ; 
 unsigned int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_WRITE_SUB_OPCODE_LINEAR ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_sdma_vm_copy_pte(struct amdgpu_ib *ib,
				 uint64_t pe, uint64_t src,
				 unsigned count)
{
	unsigned bytes = count * 8;

	ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY,
		SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
	ib->ptr[ib->length_dw++] = bytes;
	ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
	ib->ptr[ib->length_dw++] = lower_32_bits(src);
	ib->ptr[ib->length_dw++] = upper_32_bits(src);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
}