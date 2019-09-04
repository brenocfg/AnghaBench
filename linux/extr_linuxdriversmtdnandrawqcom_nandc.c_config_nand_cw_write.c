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
struct qcom_nand_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_BAM_NEXT_SGL ; 
 int /*<<< orphan*/  NAND_EXEC_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_CMD ; 
 int /*<<< orphan*/  NAND_FLASH_STATUS ; 
 int /*<<< orphan*/  NAND_READ_STATUS ; 
 int /*<<< orphan*/  read_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dma (struct qcom_nand_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_nand_cw_write(struct qcom_nand_controller *nandc)
{
	write_reg_dma(nandc, NAND_FLASH_CMD, 1, NAND_BAM_NEXT_SGL);
	write_reg_dma(nandc, NAND_EXEC_CMD, 1, NAND_BAM_NEXT_SGL);

	read_reg_dma(nandc, NAND_FLASH_STATUS, 1, NAND_BAM_NEXT_SGL);

	write_reg_dma(nandc, NAND_FLASH_STATUS, 1, 0);
	write_reg_dma(nandc, NAND_READ_STATUS, 1, NAND_BAM_NEXT_SGL);
}