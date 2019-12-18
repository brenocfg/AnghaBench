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
typedef  int u32 ;
struct qcom_nand_controller {int vld; void* cmd1; TYPE_1__* props; } ;
struct TYPE_2__ {scalar_t__ is_bam; } ;

/* Variables and functions */
 int BAM_MODE_EN ; 
 int DM_EN ; 
 int /*<<< orphan*/  NAND_CTRL ; 
 int /*<<< orphan*/  NAND_DEV_CMD1 ; 
 int /*<<< orphan*/  NAND_DEV_CMD_VLD ; 
 int NAND_DEV_CMD_VLD_VAL ; 
 int /*<<< orphan*/  NAND_FLASH_CHIP_SELECT ; 
 int /*<<< orphan*/  SFLASHC_BURST_CFG ; 
 int /*<<< orphan*/  dev_cmd_reg_addr (struct qcom_nand_controller*,int /*<<< orphan*/ ) ; 
 void* nandc_read (struct qcom_nand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nandc_write (struct qcom_nand_controller*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qcom_nandc_setup(struct qcom_nand_controller *nandc)
{
	u32 nand_ctrl;

	/* kill onenand */
	nandc_write(nandc, SFLASHC_BURST_CFG, 0);
	nandc_write(nandc, dev_cmd_reg_addr(nandc, NAND_DEV_CMD_VLD),
		    NAND_DEV_CMD_VLD_VAL);

	/* enable ADM or BAM DMA */
	if (nandc->props->is_bam) {
		nand_ctrl = nandc_read(nandc, NAND_CTRL);
		nandc_write(nandc, NAND_CTRL, nand_ctrl | BAM_MODE_EN);
	} else {
		nandc_write(nandc, NAND_FLASH_CHIP_SELECT, DM_EN);
	}

	/* save the original values of these registers */
	nandc->cmd1 = nandc_read(nandc, dev_cmd_reg_addr(nandc, NAND_DEV_CMD1));
	nandc->vld = NAND_DEV_CMD_VLD_VAL;

	return 0;
}