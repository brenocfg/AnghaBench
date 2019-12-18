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
struct nand_operation {int ninstrs; int /*<<< orphan*/ * instrs; int /*<<< orphan*/  cs; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int denali_exec_instr (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  denali_reset_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  denali_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_denali_controller (struct nand_chip*) ; 

__attribute__((used)) static int denali_exec_op(struct nand_chip *chip,
			  const struct nand_operation *op, bool check_only)
{
	int i, ret;

	if (check_only)
		return 0;

	denali_select_target(chip, op->cs);

	/*
	 * Some commands contain NAND_OP_WAITRDY_INSTR.
	 * irq must be cleared here to catch the R/B# interrupt there.
	 */
	denali_reset_irq(to_denali_controller(chip));

	for (i = 0; i < op->ninstrs; i++) {
		ret = denali_exec_instr(chip, &op->instrs[i]);
		if (ret)
			return ret;
	}

	return 0;
}