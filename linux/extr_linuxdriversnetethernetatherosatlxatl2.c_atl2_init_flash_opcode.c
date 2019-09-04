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
struct atl2_hw {size_t flash_vendor; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmdREAD; int /*<<< orphan*/  cmdWRSR; int /*<<< orphan*/  cmdRDSR; int /*<<< orphan*/  cmdWREN; int /*<<< orphan*/  cmdRDID; int /*<<< orphan*/  cmdCHIP_ERASE; int /*<<< orphan*/  cmdSECTOR_ERASE; int /*<<< orphan*/  cmdPROGRAM; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ATL2_WRITE_REGB (struct atl2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_CHIP_ERASE ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_PROGRAM ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_RDID ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_RDSR ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_READ ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_SC_ERASE ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_WREN ; 
 int /*<<< orphan*/  REG_SPI_FLASH_OP_WRSR ; 
 TYPE_1__* flash_table ; 

__attribute__((used)) static void atl2_init_flash_opcode(struct atl2_hw *hw)
{
	if (hw->flash_vendor >= ARRAY_SIZE(flash_table))
		hw->flash_vendor = 0; /* ATMEL */

	/* Init OP table */
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_PROGRAM,
		flash_table[hw->flash_vendor].cmdPROGRAM);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_SC_ERASE,
		flash_table[hw->flash_vendor].cmdSECTOR_ERASE);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_CHIP_ERASE,
		flash_table[hw->flash_vendor].cmdCHIP_ERASE);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_RDID,
		flash_table[hw->flash_vendor].cmdRDID);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_WREN,
		flash_table[hw->flash_vendor].cmdWREN);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_RDSR,
		flash_table[hw->flash_vendor].cmdRDSR);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_WRSR,
		flash_table[hw->flash_vendor].cmdWRSR);
	ATL2_WRITE_REGB(hw, REG_SPI_FLASH_OP_READ,
		flash_table[hw->flash_vendor].cmdREAD);
}