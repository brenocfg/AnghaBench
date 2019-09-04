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
struct arch_probes_insn {int dummy; } ;
typedef  int /*<<< orphan*/  probes_opcode_t ;
typedef  enum probes_insn { ____Placeholder_probes_insn } probes_insn ;

/* Variables and functions */
 int decode_wb_pc (int /*<<< orphan*/ ,struct arch_probes_insn*,struct decode_header const*,int) ; 

enum probes_insn
decode_ldr(probes_opcode_t insn, struct arch_probes_insn *asi,
	   const struct decode_header *d)
{
	return decode_wb_pc(insn, asi, d, false);
}