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
struct insn {char* opcode; char* format; int name_len; char* name; char* upper; TYPE_1__* type; } ;
struct TYPE_2__ {scalar_t__ byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_opcode(struct insn *insn, int nr)
{
	char *opcode;

	opcode = insn->opcode;
	if (insn->type->byte != 0)
		opcode += 2;
	printf("\t[%4d] = { .opfrag = 0x%s, .format = INSTR_%s, ", nr, opcode, insn->format);
	if (insn->name_len < 6)
		printf(".name = \"%s\" ", insn->name);
	else
		printf(".offset = LONG_INSN_%s ", insn->upper);
	printf("}, \\\n");
}