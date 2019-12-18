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
struct nandc_regs {int /*<<< orphan*/  read_location3; int /*<<< orphan*/  read_location2; int /*<<< orphan*/  read_location1; int /*<<< orphan*/  read_location0; int /*<<< orphan*/  ecc_buf_cfg; int /*<<< orphan*/  orig_vld; int /*<<< orphan*/  vld; int /*<<< orphan*/  orig_cmd1; int /*<<< orphan*/  cmd1; int /*<<< orphan*/  clrreadstatus; int /*<<< orphan*/  ecc_bch_cfg; int /*<<< orphan*/  cfg1; int /*<<< orphan*/  cfg0; int /*<<< orphan*/  clrflashstatus; int /*<<< orphan*/  exec; int /*<<< orphan*/  chip_sel; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr0; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  NAND_ADDR0 146 
#define  NAND_ADDR1 145 
#define  NAND_DEV0_CFG0 144 
#define  NAND_DEV0_CFG1 143 
#define  NAND_DEV0_ECC_CFG 142 
#define  NAND_DEV_CMD1 141 
#define  NAND_DEV_CMD1_RESTORE 140 
#define  NAND_DEV_CMD_VLD 139 
#define  NAND_DEV_CMD_VLD_RESTORE 138 
#define  NAND_EBI2_ECC_BUF_CFG 137 
#define  NAND_EXEC_CMD 136 
#define  NAND_FLASH_CHIP_SELECT 135 
#define  NAND_FLASH_CMD 134 
#define  NAND_FLASH_STATUS 133 
#define  NAND_READ_LOCATION_0 132 
#define  NAND_READ_LOCATION_1 131 
#define  NAND_READ_LOCATION_2 130 
#define  NAND_READ_LOCATION_3 129 
#define  NAND_READ_STATUS 128 

__attribute__((used)) static __le32 *offset_to_nandc_reg(struct nandc_regs *regs, int offset)
{
	switch (offset) {
	case NAND_FLASH_CMD:
		return &regs->cmd;
	case NAND_ADDR0:
		return &regs->addr0;
	case NAND_ADDR1:
		return &regs->addr1;
	case NAND_FLASH_CHIP_SELECT:
		return &regs->chip_sel;
	case NAND_EXEC_CMD:
		return &regs->exec;
	case NAND_FLASH_STATUS:
		return &regs->clrflashstatus;
	case NAND_DEV0_CFG0:
		return &regs->cfg0;
	case NAND_DEV0_CFG1:
		return &regs->cfg1;
	case NAND_DEV0_ECC_CFG:
		return &regs->ecc_bch_cfg;
	case NAND_READ_STATUS:
		return &regs->clrreadstatus;
	case NAND_DEV_CMD1:
		return &regs->cmd1;
	case NAND_DEV_CMD1_RESTORE:
		return &regs->orig_cmd1;
	case NAND_DEV_CMD_VLD:
		return &regs->vld;
	case NAND_DEV_CMD_VLD_RESTORE:
		return &regs->orig_vld;
	case NAND_EBI2_ECC_BUF_CFG:
		return &regs->ecc_buf_cfg;
	case NAND_READ_LOCATION_0:
		return &regs->read_location0;
	case NAND_READ_LOCATION_1:
		return &regs->read_location1;
	case NAND_READ_LOCATION_2:
		return &regs->read_location2;
	case NAND_READ_LOCATION_3:
		return &regs->read_location3;
	default:
		return NULL;
	}
}