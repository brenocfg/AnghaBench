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
struct pic32_sec_osc {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  enable_mask; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 struct pic32_sec_osc* clkhw_to_sosc (struct clk_hw*) ; 
 int /*<<< orphan*/  pic32_syskey_unlock () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sosc_clk_disable(struct clk_hw *hw)
{
	struct pic32_sec_osc *sosc = clkhw_to_sosc(hw);

	pic32_syskey_unlock();
	writel(sosc->enable_mask, PIC32_CLR(sosc->enable_reg));
}