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
typedef  int /*<<< orphan*/  u8 ;
struct nand_operation {int dummy; } ;
struct nand_op_instr {int dummy; } ;
struct nand_chip {int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hynix_nand_cmd_op(struct nand_chip *chip, u8 cmd)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (chip->exec_op) {
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(cmd, 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		return nand_exec_op(chip, &op);
	}

	chip->cmdfunc(mtd, cmd, -1, -1);

	return 0;
}