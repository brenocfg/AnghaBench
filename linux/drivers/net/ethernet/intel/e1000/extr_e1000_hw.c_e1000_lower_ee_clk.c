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
struct TYPE_2__ {int /*<<< orphan*/  delay_usec; } ;
struct e1000_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int E1000_EECD_SK ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_lower_ee_clk(struct e1000_hw *hw, u32 *eecd)
{
	/* Lower the clock input to the EEPROM (by clearing the SK bit), and
	 * then wait 50 microseconds.
	 */
	*eecd = *eecd & ~E1000_EECD_SK;
	ew32(EECD, *eecd);
	E1000_WRITE_FLUSH();
	udelay(hw->eeprom.delay_usec);
}