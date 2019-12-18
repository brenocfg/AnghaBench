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
struct nand_operation {int dummy; } ;
struct nand_op_instr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_delay; int /*<<< orphan*/  dev_ready; } ;
struct nand_chip {TYPE_1__ legacy; int /*<<< orphan*/  cur_cs; } ;

/* Variables and functions */
 struct nand_operation NAND_OPERATION (int /*<<< orphan*/ ,struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (unsigned int) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (unsigned int) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_wait_ready (struct nand_chip*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_wait_rdy_op(struct nand_chip *chip, unsigned int timeout_ms,
			    unsigned int delay_ns)
{
	if (nand_has_exec_op(chip)) {
		struct nand_op_instr instrs[] = {
			NAND_OP_WAIT_RDY(PSEC_TO_MSEC(timeout_ms),
					 PSEC_TO_NSEC(delay_ns)),
		};
		struct nand_operation op = NAND_OPERATION(chip->cur_cs, instrs);

		return nand_exec_op(chip, &op);
	}

	/* Apply delay or wait for ready/busy pin */
	if (!chip->legacy.dev_ready)
		udelay(chip->legacy.chip_delay);
	else
		nand_wait_ready(chip);

	return 0;
}