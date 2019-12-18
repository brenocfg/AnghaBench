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
struct nand_operation {int /*<<< orphan*/  cs; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc {TYPE_1__* caps; } ;
struct TYPE_2__ {scalar_t__ is_nfcv2; } ;

/* Variables and functions */
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfcv1_op_parser ; 
 int /*<<< orphan*/  marvell_nfcv2_op_parser ; 
 int nand_op_parser_exec_op (struct nand_chip*,int /*<<< orphan*/ *,struct nand_operation const*,int) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nfc_exec_op(struct nand_chip *chip,
			       const struct nand_operation *op,
			       bool check_only)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);

	marvell_nfc_select_target(chip, op->cs);

	if (nfc->caps->is_nfcv2)
		return nand_op_parser_exec_op(chip, &marvell_nfcv2_op_parser,
					      op, check_only);
	else
		return nand_op_parser_exec_op(chip, &marvell_nfcv1_op_parser,
					      op, check_only);
}