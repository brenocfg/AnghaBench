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
struct e1000_hw {TYPE_1__ nvm; } ;

/* Variables and functions */
 int E1000_EECD_SK ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_raise_eec_clk(struct e1000_hw *hw, u32 *eecd)
{
	*eecd = *eecd | E1000_EECD_SK;
	ew32(EECD, *eecd);
	e1e_flush();
	udelay(hw->nvm.delay_usec);
}