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
struct qcom_nand_host {struct nand_chip chip; } ;
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_BAM_NEXT_SGL ; 
 int /*<<< orphan*/  NAND_EXEC_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_STATUS ; 
 int OP_RESET_DEVICE ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nandc_set_reg (struct qcom_nand_controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset(struct qcom_nand_host *host)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	nandc_set_reg(nandc, NAND_FLASH_CMD, OP_RESET_DEVICE);
	nandc_set_reg(nandc, NAND_EXEC_CMD, 1);

	write_reg_dma(nandc, NAND_FLASH_CMD, 1, NAND_BAM_NEXT_SGL);
	write_reg_dma(nandc, NAND_EXEC_CMD, 1, NAND_BAM_NEXT_SGL);

	read_reg_dma(nandc, NAND_FLASH_STATUS, 1, NAND_BAM_NEXT_SGL);

	return 0;
}