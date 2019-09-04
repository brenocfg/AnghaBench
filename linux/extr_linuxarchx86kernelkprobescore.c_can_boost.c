#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nbytes; int* bytes; } ;
struct insn {TYPE_1__ opcode; int /*<<< orphan*/  attr; } ;
typedef  int kprobe_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  inat_is_address_size_prefix (int /*<<< orphan*/ ) ; 
 scalar_t__ search_exception_tables (unsigned long) ; 
 int test_bit (int,unsigned long*) ; 
 scalar_t__ twobyte_is_boostable ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int can_boost(struct insn *insn, void *addr)
{
	kprobe_opcode_t opcode;

	if (search_exception_tables((unsigned long)addr))
		return 0;	/* Page fault may occur on this address. */

	/* 2nd-byte opcode */
	if (insn->opcode.nbytes == 2)
		return test_bit(insn->opcode.bytes[1],
				(unsigned long *)twobyte_is_boostable);

	if (insn->opcode.nbytes != 1)
		return 0;

	/* Can't boost Address-size override prefix */
	if (unlikely(inat_is_address_size_prefix(insn->attr)))
		return 0;

	opcode = insn->opcode.bytes[0];

	switch (opcode & 0xf0) {
	case 0x60:
		/* can't boost "bound" */
		return (opcode != 0x62);
	case 0x70:
		return 0; /* can't boost conditional jump */
	case 0x90:
		return opcode != 0x9a;	/* can't boost call far */
	case 0xc0:
		/* can't boost software-interruptions */
		return (0xc1 < opcode && opcode < 0xcc) || opcode == 0xcf;
	case 0xd0:
		/* can boost AA* and XLAT */
		return (opcode == 0xd4 || opcode == 0xd5 || opcode == 0xd7);
	case 0xe0:
		/* can boost in/out and absolute jmps */
		return ((opcode & 0x04) || opcode == 0xea);
	case 0xf0:
		/* clear and set flags are boostable */
		return (opcode == 0xf5 || (0xf7 < opcode && opcode < 0xfe));
	default:
		/* CS override prefix and call are not boostable */
		return (opcode != 0x2e && opcode != 0x9a);
	}
}