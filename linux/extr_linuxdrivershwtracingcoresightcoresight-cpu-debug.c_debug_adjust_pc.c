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
struct debug_drvdata {int /*<<< orphan*/  dev; scalar_t__ pc_has_offset; scalar_t__ edpcsr; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 unsigned long EDPCSR_ARM_INST_MASK ; 
 unsigned long EDPCSR_THUMB ; 
 unsigned long EDPCSR_THUMB_INST_MASK ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned long debug_adjust_pc(struct debug_drvdata *drvdata)
{
	unsigned long arm_inst_offset = 0, thumb_inst_offset = 0;
	unsigned long pc;

	pc = (unsigned long)drvdata->edpcsr;

	if (drvdata->pc_has_offset) {
		arm_inst_offset = 8;
		thumb_inst_offset = 4;
	}

	/* Handle thumb instruction */
	if (pc & EDPCSR_THUMB) {
		pc = (pc & EDPCSR_THUMB_INST_MASK) - thumb_inst_offset;
		return pc;
	}

	/*
	 * Handle arm instruction offset, if the arm instruction
	 * is not 4 byte alignment then it's possible the case
	 * for implementation defined; keep original value for this
	 * case and print info for notice.
	 */
	if (pc & BIT(1))
		dev_emerg(drvdata->dev,
			  "Instruction offset is implementation defined\n");
	else
		pc = (pc & EDPCSR_ARM_INST_MASK) - arm_inst_offset;

	return pc;
}