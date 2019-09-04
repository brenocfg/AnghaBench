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
struct gen_opcode {int nr; TYPE_1__* insn; } ;
struct TYPE_2__ {char* format; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmpformat ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void print_formats(struct gen_opcode *desc)
{
	char *format;
	int i, count;

	qsort(desc->insn, desc->nr, sizeof(*desc->insn), cmpformat);
	format = "";
	count = 0;
	printf("enum {\n");
	for (i = 0; i < desc->nr; i++) {
		if (!strcmp(format, desc->insn[i].format))
			continue;
		count++;
		format = desc->insn[i].format;
		printf("\tINSTR_%s,\n", format);
	}
	printf("}; /* %d */\n\n", count);
}