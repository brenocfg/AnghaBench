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
struct decode_header {int dummy; } ;
struct arch_probes_insn {int stack_space; } ;
typedef  int probes_opcode_t ;
typedef  enum probes_insn { ____Placeholder_probes_insn } probes_insn ;

/* Variables and functions */
 int INSN_GOOD_NO_SLOT ; 

enum probes_insn checker_stack_use_imm_xxx(probes_opcode_t insn,
		struct arch_probes_insn *asi,
		const struct decode_header *h)
{
	int imm = insn & 0xfff;
	asi->stack_space = imm;
	return INSN_GOOD_NO_SLOT;
}