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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD_CS ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  e1000_lower_eec_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_nvm_eeprom_spi ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_stop_nvm(struct e1000_hw *hw)
{
	u32 eecd;

	eecd = er32(EECD);
	if (hw->nvm.type == e1000_nvm_eeprom_spi) {
		/* Pull CS high */
		eecd |= E1000_EECD_CS;
		e1000_lower_eec_clk(hw, &eecd);
	}
}