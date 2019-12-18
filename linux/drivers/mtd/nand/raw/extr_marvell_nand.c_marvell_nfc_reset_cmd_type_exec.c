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
struct nand_subop {int dummy; } ;
struct nand_chip {int dummy; } ;
struct marvell_nfc_op {int /*<<< orphan*/  rdy_delay_ns; int /*<<< orphan*/  rdy_timeout_ms; int /*<<< orphan*/  cle_ale_delay_ns; int /*<<< orphan*/ * ndcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDCB0_CMD_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_RESET ; 
 int /*<<< orphan*/  cond_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_parse_instructions (struct nand_chip*,struct nand_subop const*,struct marvell_nfc_op*) ; 
 int marvell_nfc_prepare_cmd (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_send_cmd (struct nand_chip*,struct marvell_nfc_op*) ; 
 int marvell_nfc_wait_cmdd (struct nand_chip*) ; 
 int marvell_nfc_wait_op (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nfc_reset_cmd_type_exec(struct nand_chip *chip,
					   const struct nand_subop *subop)
{
	struct marvell_nfc_op nfc_op;
	int ret;

	marvell_nfc_parse_instructions(chip, subop, &nfc_op);
	nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_RESET);

	ret = marvell_nfc_prepare_cmd(chip);
	if (ret)
		return ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_wait_cmdd(chip);
	if (ret)
		return ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	ret = marvell_nfc_wait_op(chip, nfc_op.rdy_timeout_ms);
	if (ret)
		return ret;

	cond_delay(nfc_op.rdy_delay_ns);

	return 0;
}