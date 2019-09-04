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
struct e1000_eeprom_info {scalar_t__ type; int /*<<< orphan*/  delay_usec; } ;
struct e1000_hw {struct e1000_eeprom_info eeprom; } ;

/* Variables and functions */
 int E1000_EECD_CS ; 
 int E1000_EECD_SK ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  EECD ; 
 scalar_t__ e1000_eeprom_microwire ; 
 scalar_t__ e1000_eeprom_spi ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_standby_eeprom(struct e1000_hw *hw)
{
	struct e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd;

	eecd = er32(EECD);

	if (eeprom->type == e1000_eeprom_microwire) {
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Clock high */
		eecd |= E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Select EEPROM */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Clock low */
		eecd &= ~E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
	} else if (eeprom->type == e1000_eeprom_spi) {
		/* Toggle CS to flush commands */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
		eecd &= ~E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
	}
}