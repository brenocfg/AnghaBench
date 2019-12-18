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
struct marvell_nfc_op {int /*<<< orphan*/  rdy_delay_ns; int /*<<< orphan*/  rdy_timeout_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_parse_instructions (struct nand_chip*,struct nand_subop const*,struct marvell_nfc_op*) ; 
 int marvell_nfc_wait_op (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nfc_naked_waitrdy_exec(struct nand_chip *chip,
					  const struct nand_subop *subop)
{
	struct marvell_nfc_op nfc_op;
	int ret;

	marvell_nfc_parse_instructions(chip, subop, &nfc_op);

	ret = marvell_nfc_wait_op(chip, nfc_op.rdy_timeout_ms);
	cond_delay(nfc_op.rdy_delay_ns);

	return ret;
}