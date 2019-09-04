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
struct rockchip_inv_clock {int shift; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int INVERTER_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct rockchip_inv_clock* to_inv_clock (struct clk_hw*) ; 

__attribute__((used)) static int rockchip_inv_get_phase(struct clk_hw *hw)
{
	struct rockchip_inv_clock *inv_clock = to_inv_clock(hw);
	u32 val;

	val = readl(inv_clock->reg) >> inv_clock->shift;
	val &= INVERTER_MASK;
	return val ? 180 : 0;
}