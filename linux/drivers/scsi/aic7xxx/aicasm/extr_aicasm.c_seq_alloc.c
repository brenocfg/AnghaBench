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
struct instruction {int /*<<< orphan*/  srcline; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct instruction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct instruction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_program ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylineno ; 

struct instruction *
seq_alloc()
{
	struct instruction *new_instr;

	new_instr = (struct instruction *)malloc(sizeof(struct instruction));
	if (new_instr == NULL)
		stop("Unable to malloc instruction object", EX_SOFTWARE);
	memset(new_instr, 0, sizeof(*new_instr));
	STAILQ_INSERT_TAIL(&seq_program, new_instr, links);
	new_instr->srcline = yylineno;
	return new_instr;
}