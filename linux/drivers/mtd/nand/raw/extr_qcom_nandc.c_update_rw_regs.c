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
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct qcom_nand_host {unsigned int cfg0; int cfg1; int ecc_bch_cfg; unsigned int cfg0_raw; int cfg1_raw; int ecc_buf_cfg; int clrflashstatus; int clrreadstatus; int /*<<< orphan*/  cw_size; int /*<<< orphan*/  cw_data; scalar_t__ use_ecc; struct nand_chip chip; } ;
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 unsigned int CW_PER_PAGE ; 
 int ECC_CFG_ECC_DISABLE ; 
 int LAST_PAGE ; 
 int /*<<< orphan*/  NAND_DEV0_CFG0 ; 
 int /*<<< orphan*/  NAND_DEV0_CFG1 ; 
 int /*<<< orphan*/  NAND_DEV0_ECC_CFG ; 
 int /*<<< orphan*/  NAND_EBI2_ECC_BUF_CFG ; 
 int /*<<< orphan*/  NAND_EXEC_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_STATUS ; 
 int /*<<< orphan*/  NAND_READ_STATUS ; 
 int OP_PAGE_READ ; 
 int OP_PAGE_READ_WITH_ECC ; 
 int OP_PROGRAM_PAGE ; 
 int PAGE_ACC ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nandc_set_read_loc (struct qcom_nand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nandc_set_reg (struct qcom_nand_controller*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_rw_regs(struct qcom_nand_host *host, int num_cw, bool read)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	u32 cmd, cfg0, cfg1, ecc_bch_cfg;

	if (read) {
		if (host->use_ecc)
			cmd = OP_PAGE_READ_WITH_ECC | PAGE_ACC | LAST_PAGE;
		else
			cmd = OP_PAGE_READ | PAGE_ACC | LAST_PAGE;
	} else {
		cmd = OP_PROGRAM_PAGE | PAGE_ACC | LAST_PAGE;
	}

	if (host->use_ecc) {
		cfg0 = (host->cfg0 & ~(7U << CW_PER_PAGE)) |
				(num_cw - 1) << CW_PER_PAGE;

		cfg1 = host->cfg1;
		ecc_bch_cfg = host->ecc_bch_cfg;
	} else {
		cfg0 = (host->cfg0_raw & ~(7U << CW_PER_PAGE)) |
				(num_cw - 1) << CW_PER_PAGE;

		cfg1 = host->cfg1_raw;
		ecc_bch_cfg = 1 << ECC_CFG_ECC_DISABLE;
	}

	nandc_set_reg(nandc, NAND_FLASH_CMD, cmd);
	nandc_set_reg(nandc, NAND_DEV0_CFG0, cfg0);
	nandc_set_reg(nandc, NAND_DEV0_CFG1, cfg1);
	nandc_set_reg(nandc, NAND_DEV0_ECC_CFG, ecc_bch_cfg);
	nandc_set_reg(nandc, NAND_EBI2_ECC_BUF_CFG, host->ecc_buf_cfg);
	nandc_set_reg(nandc, NAND_FLASH_STATUS, host->clrflashstatus);
	nandc_set_reg(nandc, NAND_READ_STATUS, host->clrreadstatus);
	nandc_set_reg(nandc, NAND_EXEC_CMD, 1);

	if (read)
		nandc_set_read_loc(nandc, 0, 0, host->use_ecc ?
				   host->cw_data : host->cw_size, 1);
}