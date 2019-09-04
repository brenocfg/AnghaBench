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
struct nand_chip {int dummy; } ;
struct qcom_nand_host {int cfg0_raw; int cfg1_raw; int clrflashstatus; int clrreadstatus; struct nand_chip chip; } ;
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 int CW_PER_PAGE ; 
 int LAST_PAGE ; 
 int /*<<< orphan*/  NAND_ADDR0 ; 
 int /*<<< orphan*/  NAND_ADDR1 ; 
 int /*<<< orphan*/  NAND_BAM_NEXT_SGL ; 
 int /*<<< orphan*/  NAND_DEV0_CFG0 ; 
 int /*<<< orphan*/  NAND_DEV0_CFG1 ; 
 int /*<<< orphan*/  NAND_EXEC_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_STATUS ; 
 int /*<<< orphan*/  NAND_READ_STATUS ; 
 int OP_BLOCK_ERASE ; 
 int PAGE_ACC ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nandc_set_reg (struct qcom_nand_controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erase_block(struct qcom_nand_host *host, int page_addr)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	nandc_set_reg(nandc, NAND_FLASH_CMD,
		      OP_BLOCK_ERASE | PAGE_ACC | LAST_PAGE);
	nandc_set_reg(nandc, NAND_ADDR0, page_addr);
	nandc_set_reg(nandc, NAND_ADDR1, 0);
	nandc_set_reg(nandc, NAND_DEV0_CFG0,
		      host->cfg0_raw & ~(7 << CW_PER_PAGE));
	nandc_set_reg(nandc, NAND_DEV0_CFG1, host->cfg1_raw);
	nandc_set_reg(nandc, NAND_EXEC_CMD, 1);
	nandc_set_reg(nandc, NAND_FLASH_STATUS, host->clrflashstatus);
	nandc_set_reg(nandc, NAND_READ_STATUS, host->clrreadstatus);

	write_reg_dma(nandc, NAND_FLASH_CMD, 3, NAND_BAM_NEXT_SGL);
	write_reg_dma(nandc, NAND_DEV0_CFG0, 2, NAND_BAM_NEXT_SGL);
	write_reg_dma(nandc, NAND_EXEC_CMD, 1, NAND_BAM_NEXT_SGL);

	read_reg_dma(nandc, NAND_FLASH_STATUS, 1, NAND_BAM_NEXT_SGL);

	write_reg_dma(nandc, NAND_FLASH_STATUS, 1, 0);
	write_reg_dma(nandc, NAND_READ_STATUS, 1, NAND_BAM_NEXT_SGL);

	return 0;
}