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
typedef  int u16 ;
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_DATA_OUT ; 
 int /*<<< orphan*/  drop_gpio (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_clk (struct ksz_hw*) ; 
 int /*<<< orphan*/  raise_gpio (struct ksz_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_w(struct ksz_hw *hw, u16 data)
{
	int i;

	for (i = 15; i >= 0; i--) {
		(data & (0x01 << i)) ? raise_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	}
}