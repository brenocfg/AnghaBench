#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uprobe_opcode_t ;
struct TYPE_6__ {int /*<<< orphan*/  rt; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; } ;
struct TYPE_4__ {int opcode; } ;
union mips_instruction {TYPE_3__ u_format; TYPE_2__ r_format; TYPE_1__ i_format; int /*<<< orphan*/  word; } ;

/* Variables and functions */
#define  bcond_op 142 
#define  break_op 141 
#define  spec_op 140 
#define  teq_op 139 
#define  teqi_op 138 
#define  tge_op 137 
#define  tgei_op 136 
#define  tgeiu_op 135 
#define  tgeu_op 134 
#define  tlt_op 133 
#define  tlti_op 132 
#define  tltiu_op 131 
#define  tltu_op 130 
#define  tne_op 129 
#define  tnei_op 128 

bool is_trap_insn(uprobe_opcode_t *insn)
{
	union mips_instruction inst;

	inst.word = *insn;

	switch (inst.i_format.opcode) {
	case spec_op:
		switch (inst.r_format.func) {
		case break_op:
		case teq_op:
		case tge_op:
		case tgeu_op:
		case tlt_op:
		case tltu_op:
		case tne_op:
			return 1;
		}
		break;

	case bcond_op:	/* Yes, really ...  */
		switch (inst.u_format.rt) {
		case teqi_op:
		case tgei_op:
		case tgeiu_op:
		case tlti_op:
		case tltiu_op:
		case tnei_op:
			return 1;
		}
		break;
	}

	return 0;
}