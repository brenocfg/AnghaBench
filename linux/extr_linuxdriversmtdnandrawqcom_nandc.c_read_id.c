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
struct nand_chip {int dummy; } ;
struct qcom_nand_host {struct nand_chip chip; } ;
struct qcom_nand_controller {TYPE_1__* props; } ;
struct TYPE_2__ {scalar_t__ is_bam; } ;

/* Variables and functions */
 int DM_EN ; 
 int /*<<< orphan*/  NAND_ADDR0 ; 
 int /*<<< orphan*/  NAND_ADDR1 ; 
 int /*<<< orphan*/  NAND_BAM_NEXT_SGL ; 
 int /*<<< orphan*/  NAND_EXEC_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_CHIP_SELECT ; 
 int /*<<< orphan*/  NAND_FLASH_CMD ; 
 int /*<<< orphan*/  NAND_READ_ID ; 
 int OP_FETCH_ID ; 
 struct qcom_nand_controller* get_qcom_nand_controller (struct nand_chip*) ; 
 int /*<<< orphan*/  nandc_set_reg (struct qcom_nand_controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_id(struct qcom_nand_host *host, int column)
{
	struct nand_chip *chip = &host->chip;
	struct qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	if (column == -1)
		return 0;

	nandc_set_reg(nandc, NAND_FLASH_CMD, OP_FETCH_ID);
	nandc_set_reg(nandc, NAND_ADDR0, column);
	nandc_set_reg(nandc, NAND_ADDR1, 0);
	nandc_set_reg(nandc, NAND_FLASH_CHIP_SELECT,
		      nandc->props->is_bam ? 0 : DM_EN);
	nandc_set_reg(nandc, NAND_EXEC_CMD, 1);

	write_reg_dma(nandc, NAND_FLASH_CMD, 4, NAND_BAM_NEXT_SGL);
	write_reg_dma(nandc, NAND_EXEC_CMD, 1, NAND_BAM_NEXT_SGL);

	read_reg_dma(nandc, NAND_READ_ID, 1, NAND_BAM_NEXT_SGL);

	return 0;
}