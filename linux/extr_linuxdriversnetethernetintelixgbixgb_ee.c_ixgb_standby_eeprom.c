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
typedef  int u32 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EECD ; 
 int IXGB_EECD_CS ; 
 int IXGB_EECD_SK ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_FLUSH (struct ixgb_hw*) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
ixgb_standby_eeprom(struct ixgb_hw *hw)
{
	u32 eecd_reg;

	eecd_reg = IXGB_READ_REG(hw, EECD);

	/*  Deselect EEPROM  */
	eecd_reg &= ~(IXGB_EECD_CS | IXGB_EECD_SK);
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Clock high  */
	eecd_reg |= IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Select EEPROM  */
	eecd_reg |= IXGB_EECD_CS;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Clock low  */
	eecd_reg &= ~IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);
}