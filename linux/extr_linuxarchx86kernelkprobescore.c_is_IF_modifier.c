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
typedef  int kprobe_opcode_t ;

/* Variables and functions */
 int* skip_prefixes (int*) ; 

__attribute__((used)) static int is_IF_modifier(kprobe_opcode_t *insn)
{
	/* Skip prefixes */
	insn = skip_prefixes(insn);

	switch (*insn) {
	case 0xfa:		/* cli */
	case 0xfb:		/* sti */
	case 0xcf:		/* iret/iretd */
	case 0x9d:		/* popf/popfd */
		return 1;
	}

	return 0;
}