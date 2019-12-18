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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT93C_CODE ; 
 int /*<<< orphan*/  AT93C_ERASE ; 
 int /*<<< orphan*/  AT93C_WRITE ; 
 int /*<<< orphan*/  AT93C_WR_OFF ; 
 int /*<<< orphan*/  AT93C_WR_ON ; 
 int EEPROM_ACCESS_ENABLE ; 
 int EEPROM_CHIP_SELECT ; 
 int /*<<< orphan*/  EEPROM_DATA_IN ; 
 int /*<<< orphan*/  drop_gpio (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  raise_gpio (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  spi_reg (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_w (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_gpio (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void eeprom_write(struct ksz_hw *hw, u8 reg, u16 data)
{
	int timeout;

	raise_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);

	/* Enable write. */
	spi_reg(hw, AT93C_CODE, AT93C_WR_ON);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Erase the register. */
	raise_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_ERASE, reg);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Check operation complete. */
	raise_gpio(hw, EEPROM_CHIP_SELECT);
	timeout = 8;
	mdelay(2);
	do {
		mdelay(1);
	} while (!state_gpio(hw, EEPROM_DATA_IN) && --timeout);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Write the register. */
	raise_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_WRITE, reg);
	spi_w(hw, data);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Check operation complete. */
	raise_gpio(hw, EEPROM_CHIP_SELECT);
	timeout = 8;
	mdelay(2);
	do {
		mdelay(1);
	} while (!state_gpio(hw, EEPROM_DATA_IN) && --timeout);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Disable write. */
	raise_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_CODE, AT93C_WR_OFF);

	drop_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);
}