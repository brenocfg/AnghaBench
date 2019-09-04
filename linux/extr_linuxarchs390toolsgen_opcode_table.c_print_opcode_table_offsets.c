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
struct insn_group {char* opcode; int offset; int count; TYPE_1__* type; } ;
struct gen_opcode {int nr_groups; struct insn_group* group; } ;
struct TYPE_2__ {int mask; int byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_opcode_table_offsets(struct gen_opcode *desc)
{
	struct insn_group *group;
	int i;

	printf("#define OPCODE_OFFSET_INITIALIZER { \\\n");
	for (i = 0; i < desc->nr_groups; i++) {
		group = &desc->group[i];
		printf("\t{ .opcode = 0x%.2s, .mask = 0x%02x, .byte = %d, .offset = %d, .count = %d }, \\\n",
		       group->opcode, group->type->mask, group->type->byte, group->offset, group->count);
	}
	printf("}\n\n");
}