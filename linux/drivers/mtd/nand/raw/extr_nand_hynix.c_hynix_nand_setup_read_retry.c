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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int dummy; } ;
struct hynix_nand {TYPE_1__* read_retry; } ;
struct TYPE_2__ {int nregs; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_HYNIX_CMD_APPLY_PARAMS ; 
 int /*<<< orphan*/  NAND_HYNIX_CMD_SET_PARAMS ; 
 int hynix_nand_cmd_op (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int hynix_nand_reg_write_op (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 struct hynix_nand* nand_get_manufacturer_data (struct nand_chip*) ; 

__attribute__((used)) static int hynix_nand_setup_read_retry(struct nand_chip *chip, int retry_mode)
{
	struct hynix_nand *hynix = nand_get_manufacturer_data(chip);
	const u8 *values;
	int i, ret;

	values = hynix->read_retry->values +
		 (retry_mode * hynix->read_retry->nregs);

	/* Enter 'Set Hynix Parameters' mode */
	ret = hynix_nand_cmd_op(chip, NAND_HYNIX_CMD_SET_PARAMS);
	if (ret)
		return ret;

	/*
	 * Configure the NAND in the requested read-retry mode.
	 * This is done by setting pre-defined values in internal NAND
	 * registers.
	 *
	 * The set of registers is NAND specific, and the values are either
	 * predefined or extracted from an OTP area on the NAND (values are
	 * probably tweaked at production in this case).
	 */
	for (i = 0; i < hynix->read_retry->nregs; i++) {
		ret = hynix_nand_reg_write_op(chip, hynix->read_retry->regs[i],
					      values[i]);
		if (ret)
			return ret;
	}

	/* Apply the new settings. */
	return hynix_nand_cmd_op(chip, NAND_HYNIX_CMD_APPLY_PARAMS);
}