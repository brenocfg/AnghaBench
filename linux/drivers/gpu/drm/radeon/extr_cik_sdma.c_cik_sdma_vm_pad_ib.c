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
struct radeon_ib {int length_dw; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_NOP ; 
 int /*<<< orphan*/  SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cik_sdma_vm_pad_ib(struct radeon_ib *ib)
{
	while (ib->length_dw & 0x7)
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0);
}