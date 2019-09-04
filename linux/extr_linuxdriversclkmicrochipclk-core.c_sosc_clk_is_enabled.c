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
struct pic32_sec_osc {int enable_mask; int status_mask; int /*<<< orphan*/  status_reg; int /*<<< orphan*/  enable_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct pic32_sec_osc* clkhw_to_sosc (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sosc_clk_is_enabled(struct clk_hw *hw)
{
	struct pic32_sec_osc *sosc = clkhw_to_sosc(hw);
	u32 enabled, ready;

	/* check enabled and ready status */
	enabled = readl(sosc->enable_reg) & sosc->enable_mask;
	ready = readl(sosc->status_reg) & sosc->status_mask;

	return enabled && ready;
}