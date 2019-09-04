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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_nvm_info {scalar_t__ type; int /*<<< orphan*/  delay_usec; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD_CS ; 
 int /*<<< orphan*/  EECD ; 
 scalar_t__ e1000_nvm_eeprom_spi ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_standby_nvm(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);

	if (nvm->type == e1000_nvm_eeprom_spi) {
		/* Toggle CS to flush commands */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_flush();
		udelay(nvm->delay_usec);
		eecd &= ~E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_flush();
		udelay(nvm->delay_usec);
	}
}