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
struct nand_operation {int dummy; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int nand_op_parser_exec_op (struct nand_chip*,int /*<<< orphan*/ *,struct nand_operation const*,int) ; 
 int /*<<< orphan*/  tegra_nand_op_parser ; 

__attribute__((used)) static int tegra_nand_exec_op(struct nand_chip *chip,
			      const struct nand_operation *op,
			      bool check_only)
{
	return nand_op_parser_exec_op(chip, &tegra_nand_op_parser, op,
				      check_only);
}