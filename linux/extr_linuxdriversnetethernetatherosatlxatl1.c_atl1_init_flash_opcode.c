#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atl1_hw {size_t flash_vendor; scalar_t__ hw_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_read; int /*<<< orphan*/  cmd_wrsr; int /*<<< orphan*/  cmd_rdsr; int /*<<< orphan*/  cmd_wren; int /*<<< orphan*/  cmd_rdid; int /*<<< orphan*/  cmd_chip_erase; int /*<<< orphan*/  cmd_sector_erase; int /*<<< orphan*/  cmd_program; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ REG_SPI_FLASH_OP_CHIP_ERASE ; 
 scalar_t__ REG_SPI_FLASH_OP_PROGRAM ; 
 scalar_t__ REG_SPI_FLASH_OP_RDID ; 
 scalar_t__ REG_SPI_FLASH_OP_RDSR ; 
 scalar_t__ REG_SPI_FLASH_OP_READ ; 
 scalar_t__ REG_SPI_FLASH_OP_SC_ERASE ; 
 scalar_t__ REG_SPI_FLASH_OP_WREN ; 
 scalar_t__ REG_SPI_FLASH_OP_WRSR ; 
 TYPE_1__* flash_table ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void atl1_init_flash_opcode(struct atl1_hw *hw)
{
	if (hw->flash_vendor >= ARRAY_SIZE(flash_table))
		/* Atmel */
		hw->flash_vendor = 0;

	/* Init OP table */
	iowrite8(flash_table[hw->flash_vendor].cmd_program,
		hw->hw_addr + REG_SPI_FLASH_OP_PROGRAM);
	iowrite8(flash_table[hw->flash_vendor].cmd_sector_erase,
		hw->hw_addr + REG_SPI_FLASH_OP_SC_ERASE);
	iowrite8(flash_table[hw->flash_vendor].cmd_chip_erase,
		hw->hw_addr + REG_SPI_FLASH_OP_CHIP_ERASE);
	iowrite8(flash_table[hw->flash_vendor].cmd_rdid,
		hw->hw_addr + REG_SPI_FLASH_OP_RDID);
	iowrite8(flash_table[hw->flash_vendor].cmd_wren,
		hw->hw_addr + REG_SPI_FLASH_OP_WREN);
	iowrite8(flash_table[hw->flash_vendor].cmd_rdsr,
		hw->hw_addr + REG_SPI_FLASH_OP_RDSR);
	iowrite8(flash_table[hw->flash_vendor].cmd_wrsr,
		hw->hw_addr + REG_SPI_FLASH_OP_WRSR);
	iowrite8(flash_table[hw->flash_vendor].cmd_read,
		hw->hw_addr + REG_SPI_FLASH_OP_READ);
}